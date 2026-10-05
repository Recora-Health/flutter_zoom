# R8 keep rules for the Zoom Meeting SDK

`proguard.cfg` is this plugin's consumer rules file: it is merged into the
host app's R8 configuration. It deliberately goes beyond Zoom's published
rules, and part of it is specific to the SDK version in `libs/mobilertc.aar`.
This file explains why, and what to do when the SDK is upgraded.

## Why the rules are narrower than Zoom's

From February 2027 Google Play requires apps with more than 10 MB of DEX to
reach at least 25% on each of R8 optimization, obfuscation and shrinking
(Play Console → App bundle explorer → a bundle → "DEX code optimization").

Zoom's published rules keep the whole SDK:

```
-keep class us.zoom.** { *; }
-keep class com.zipow.** { *; }
-keep class us.zipow.** { *; }
```

The SDK is about 83% of the Recora app's code, so with those rules the app
scores 17% on all three and fails. `proguard.cfg` keeps every Zoom package
except `us.zoom.proguard.**`, the SDK's already-obfuscated internal code
(roughly a fifth of the app's methods), and the app scores about 26%. The
margin is under one point.

Evidence that the released package is safe to hand to R8, for SDK 7.1.6:

- No native library references a class in it, by JNI class path
  (`us/zoom/proguard/`) or by JNI symbol (`Java_us_zoom_proguard_`). Native
  code only calls into the named packages, which stay kept.
- Only five of its classes are named in string constants, and those are kept
  whole.
- The SDK ships no keep rules of its own inside the AAR.

What releasing it exposed, each now covered by a rule in `proguard.cfg`:

| Pattern in the SDK | Failure without the rule | Rule |
|---|---|---|
| `ZMBaseStyle` reads its subclass's generic superclass (`getGenericSuperclass`) | In-meeting chat crashes opening the formatting toolbar: `Class cannot be cast to ParameterizedType` | `-keep,allowobfuscation,allowshrinking` on the base class, its subclasses and the span classes used as type arguments |
| Two `ZMBaseRecyclerViewAdapter` classes do the same | Same crash in list screens | Same rule shape on their subclasses |
| Methods found through `@SystemEvent`, `@JsMethod`, `@AsyncCall` / `@OnewayCall` | Silent: R8 removes the methods as unused | `-keepclassmembers` on annotated methods |
| `IMSettingKeyEnum` enumerates fields of its nested classes | Silent: missing settings keys | `-keepclassmembers ... { <fields>; }` |
| Private androidx / Material fields read by name (`ViewPager2.mCurrentItem`, `FragmentManager.mExecutingActions`, `ViewModelStore.map`, ...) | Silent: the lookup throws and Zoom's workaround is skipped | `-keepclassmembers` naming each member |

The last row applies whenever androidx and Material are not blanket-kept, not
only when `us.zoom.proguard` is released.

Two R8 details that bit during this work and are easy to get wrong again:

- The base class of a generic-superclass pattern must be matched by a rule
  too, not just its subclasses. Without its own signature R8 rewrites every
  `extends Base<Arg>` to the raw type and the cast still fails. Check the
  built class with `dexdump -a` and look for a
  `dalvik/annotation/Signature` value that still contains the type argument.
- The host app's `proguard-rules.pro` must not repeat the Zoom keeps. Keep
  rules are additive, so a `-keep class us.zoom.** { *; }` anywhere in the
  merged configuration silently undoes the narrowing here.

## On every Zoom SDK upgrade

Zoom's obfuscator renames the internal classes on each release, so every rule
that names a `us.zoom.proguard` class is stale after an upgrade. Stale rules
keep nothing (R8 ignores unmatched names), so the symptom is a runtime crash
or silent misbehaviour, not a build error.

1. Replace `libs/mobilertc.aar` as usual.
2. Run the report:

   ```
   python3 tool/r8_rules_report.py libs/mobilertc.aar
   ```

   It locates the relevant classes by their `SourceFile` attribute, which
   Zoom's obfuscation leaves intact, and prints:

   - native references into `us.zoom.proguard` (must stay at zero; if not,
     the release of that package is no longer safe as written);
   - classes named in string constants, with their source files;
   - every reflection user in `us.zoom.proguard`, by kind, so new patterns
     show up;
   - the generic-superclass bases with their subclasses and type arguments;
   - androidx / Material member lookups, to compare with the
     `-keepclassmembers` rules;
   - a ready-to-paste block of the version-specific rules.

3. Replace the version-specific rules in `proguard.cfg` with the block the
   report prints. Compare the reflection and androidx sections with the
   existing rules and add rules for anything new.
4. In the host app, build a release variant and read the score from
   `build/app/intermediates/r8_metadata/<variant>/minify<Variant>WithR8/r8-metadata.dat`
   (`stats`: the Play score is 100 minus each `no…Percentage`). All three
   must be at or above 25, and Play Console reports the same numbers after
   upload.
5. Device-test a release build, with `adb logcat -b crash` running. The
   paths that exercise the patterns above: in-meeting chat including the
   text-formatting toolbar, every in-meeting list (participants, audio
   source, reactions, the "more" menu), swiping video pages, host-driven
   state changes (mute, unmute request, waiting room, meeting ended), leave
   and rejoin, and background and return.

R8 rule changes are native changes for Shorebird: they need a full store
release, not a patch.
