#!/usr/bin/env python3
"""Report what proguard.cfg must name for the bundled Zoom Meeting SDK.

proguard.cfg releases us.zoom.proguard.** (the SDK's already-obfuscated
internals) to R8 and compensates for the reflection inside the SDK. Several of
those rules name obfuscated classes, and Zoom's obfuscator renames everything
on every SDK release. Run this after replacing libs/mobilertc.aar and compare
the output with proguard.cfg:

    python3 tool/r8_rules_report.py libs/mobilertc.aar

It needs only the Python standard library. Classes are located by their
SourceFile attribute (ZMBaseStyle.java, IMSettingKeyEnum.kt, ...), which
survives Zoom's obfuscation, so the report prints the names the current SDK
uses and a ready-to-paste block of the version-specific rules. See
R8_RULES.md for the full upgrade procedure.
"""
import io
import re
import struct
import sys
import zipfile
from collections import defaultdict

RELEASED_PACKAGE = "us/zoom/proguard/"

# SourceFile -> what proguard.cfg uses the class for.
ANCHORS = {
    "ZMBaseStyle.java": "generic-superclass base (chat text styles)",
    "IMSettingKeyEnum.kt": "enumerates fields of its nested key holders",
    "ZappChatAppProxy.java": "named in a string constant",
    "SearchEventTrackingUtils.java": "named in a string constant",
    "OpenCameraInterface.java": "named in a string constant",
    "ContactLinkViewModel.java": "named in a string constant",
    "ChatAppCTAImpl.java": "named in a string constant",
}

REFLECTION = {
    "generic signature": {"getGenericSuperclass", "getGenericInterfaces"},
    "member lookup by name": {"getDeclaredField", "getDeclaredMethod", "getField", "getMethod",
                              "getDeclaredFields", "getDeclaredMethods", "getMethods", "getFields"},
    "runtime annotation": {"getAnnotation", "isAnnotationPresent", "getDeclaredAnnotation",
                           "getAnnotations", "getDeclaredAnnotations"},
    "class by name": {"forName", "loadClass"},
}
REFLECTION_OWNERS = {"java/lang/Class", "java/lang/ClassLoader", "java/lang/reflect/Method",
                     "java/lang/reflect/Field", "java/lang/reflect/AccessibleObject"}


class ClassInfo:
    __slots__ = ("name", "super_name", "source", "signature", "strings", "class_refs", "reflective")

    def __init__(self):
        self.name = self.super_name = self.source = self.signature = None
        self.strings = []
        self.class_refs = set()
        self.reflective = set()


def parse_class(data):
    """Minimal class-file reader: constant pool, super class, SourceFile, Signature."""
    buf = io.BytesIO(data)
    rd = buf.read

    def u1():
        return rd(1)[0]

    def u2():
        return struct.unpack(">H", rd(2))[0]

    def u4():
        return struct.unpack(">I", rd(4))[0]

    if u4() != 0xCAFEBABE:
        return None
    rd(4)
    count = u2()
    pool = [None] * count
    i = 1
    while i < count:
        tag = u1()
        if tag == 1:
            n = u2()
            pool[i] = ("utf8", rd(n).decode("utf-8", "replace"))
        elif tag in (3, 4):
            rd(4)
        elif tag in (5, 6):
            rd(8)
            i += 1
        elif tag in (7, 8, 16, 19, 20):
            pool[i] = ("ref", tag, u2())
        elif tag in (9, 10, 11, 12, 17, 18):
            pool[i] = ("pair", tag, u2(), u2())
        elif tag == 15:
            rd(3)
        else:
            return None
        i += 1

    def utf8(idx):
        e = pool[idx]
        return e[1] if e and e[0] == "utf8" else None

    def class_name(idx):
        e = pool[idx]
        return utf8(e[2]) if e and e[0] == "ref" and e[1] == 7 else None

    info = ClassInfo()
    u2()  # access flags
    info.name = class_name(u2())
    info.super_name = class_name(u2())
    for e in pool:
        if not e:
            continue
        if e[0] == "ref" and e[1] == 7:
            n = utf8(e[2])
            if n:
                info.class_refs.add(n)
        elif e[0] == "ref" and e[1] == 8:
            s = utf8(e[2])
            if s is not None:
                info.strings.append(s)
        elif e[0] == "pair" and e[1] in (9, 10, 11):
            owner = class_name(e[2])
            nt = pool[e[3]]
            if owner in REFLECTION_OWNERS and nt and nt[0] == "pair":
                info.reflective.add(utf8(nt[2]))

    rd(2 * u2())  # interfaces

    def skip_members():
        for _ in range(u2()):
            rd(6)
            for _ in range(u2()):
                u2()
                rd(u4())

    skip_members()
    skip_members()
    for _ in range(u2()):
        name = utf8(u2())
        length = u4()
        body = rd(length)
        if name == "SourceFile":
            info.source = utf8(struct.unpack(">H", body)[0])
        elif name == "Signature":
            info.signature = utf8(struct.unpack(">H", body)[0])
    return info


def dotted(internal):
    return internal.replace("/", ".")


def main(aar_path):
    aar = zipfile.ZipFile(aar_path)
    names = aar.namelist()
    jar = zipfile.ZipFile(io.BytesIO(aar.read("classes.jar")))
    classes = {}
    for n in jar.namelist():
        if n.endswith(".class"):
            info = parse_class(jar.read(n))
            if info and info.name:
                classes[info.name] = info
    print(f"SDK classes: {len(classes)}  "
          f"(us.zoom.proguard: {sum(1 for c in classes if c.startswith(RELEASED_PACKAGE))})")

    # 1. Native references into the released package.
    print("\n== 1. Native libraries referencing us.zoom.proguard (must stay 0)")
    hits = 0
    for n in names:
        if n.startswith("jni/") and n.endswith(".so"):
            data = aar.read(n)
            found = set(re.findall(rb"us/zoom/proguard/[A-Za-z0-9_$/]+", data))
            found |= set(re.findall(rb"Java_us_zoom_proguard_[A-Za-z0-9_]+", data))
            if found:
                hits += len(found)
                print(f"  {n}: " + ", ".join(sorted(f.decode() for f in found)[:10]))
    print(f"  {hits} reference(s)")

    # 2. Released classes named in string constants or resources.
    print("\n== 2. us.zoom.proguard classes named in string constants (keep whole)")
    named = defaultdict(set)
    for c in classes.values():
        for s in c.strings:
            for m in re.findall(r"us\.zoom\.proguard\.[A-Za-z0-9_$]+", s):
                named[m].add(c.name)
    for n in names:
        if n.startswith("res/") and n.endswith(".xml"):
            for m in re.findall(rb"us\.zoom\.proguard\.[A-Za-z0-9_$]+", aar.read(n)):
                named[m.decode()].add(n)
    for cls in sorted(named):
        src = classes.get(cls.replace(".", "/"))
        print(f"  {cls:34s} {(src.source if src else '?'):36s} referenced from {len(named[cls])} place(s)")

    # 3. Anchors located by SourceFile.
    print("\n== 3. Classes proguard.cfg names, located by SourceFile")
    by_source = defaultdict(list)
    for c in classes.values():
        if c.source and c.name.startswith(RELEASED_PACKAGE) and "$" not in c.name:
            by_source[c.source].append(c.name)
    anchor_class = {}
    for src, why in ANCHORS.items():
        found = sorted(by_source.get(src, []))
        anchor_class[src] = found
        print(f"  {src:30s} -> {', '.join(dotted(f) for f in found) or 'NOT FOUND'}   ({why})")

    # 4. Reflection inside the released package.
    print("\n== 4. Reflection in us.zoom.proguard, by kind (compare with the rules in proguard.cfg)")
    for kind, methods in REFLECTION.items():
        users = sorted((c for c in classes.values()
                        if c.name.startswith(RELEASED_PACKAGE) and c.reflective & methods), key=lambda x: x.name)
        print(f"  {kind}: {len(users)} class(es)")
        for c in users:
            extra = ""
            if kind == "runtime annotation":
                anns = sorted(dotted(r) for r in c.class_refs if "annotation" in r.lower() and r.startswith("us/zoom"))
                extra = "  annotations: " + ", ".join(anns) if anns else ""
            print(f"      {dotted(c.name):28s} {c.source or '?'}{extra}")

    # 5. Generic-superclass bases: direct subclasses and their type arguments.
    print("\n== 5. Generic-superclass bases: subclasses and type arguments (keep signatures)")
    bases = [c for c in classes.values()
             if c.name.startswith(RELEASED_PACKAGE) and c.reflective & REFLECTION["generic signature"]]
    span_rules = []
    for base in bases:
        subs = sorted((c for c in classes.values() if c.super_name == base.name), key=lambda x: x.name)
        print(f"  {dotted(base.name)} ({base.source}): {len(subs)} direct subclass(es)")
        for s in subs:
            arg = None
            if s.signature:
                m = re.search(re.escape("L" + base.name) + r"<L([^;<]+);", s.signature)
                arg = m.group(1) if m else None
            print(f"      {dotted(s.name):28s} <{dotted(arg) if arg else '?'}>")
            if arg and arg.startswith(RELEASED_PACKAGE):
                span_rules.append(arg)

    # 6. androidx / Material members looked up by name anywhere in the SDK.
    print("\n== 6. Possible androidx / Material member lookups by name (compare with the -keepclassmembers rules)")
    lookup = REFLECTION["member lookup by name"]
    ident = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
    for c in sorted(classes.values(), key=lambda x: x.name):
        if not c.reflective & lookup:
            continue
        targets = sorted(dotted(r) for r in c.class_refs
                         if r.startswith(("androidx/", "com/google/android/material/")))
        targets += sorted(s for s in c.strings if s.startswith(("androidx.", "com.google.android.material.")))
        if not targets:
            continue
        members = sorted(s for s in c.strings if ident.match(s) and 3 <= len(s) <= 40)
        print(f"  {dotted(c.name)} ({c.source or '?'})")
        print(f"      targets: {', '.join(targets)}")
        print(f"      strings: {', '.join(members[:12])}")

    # 7. Suggested version-specific rules.
    print("\n== 7. Suggested version-specific rules for proguard.cfg")
    for cls in sorted(named):
        print(f"-keep class {cls} {{*;}}")
    for base in bases:
        print(f"-keep,allowobfuscation,allowshrinking class {dotted(base.name)}")
        print(f"-keep,allowobfuscation,allowshrinking class * extends {dotted(base.name)}")
    for arg in sorted(set(span_rules)):
        print(f"-keep,allowobfuscation,allowshrinking class {dotted(arg)}")
    for src in ("IMSettingKeyEnum.kt",):
        for cls in anchor_class.get(src, []):
            print(f"-keepclassmembers class {dotted(cls)}$* {{ <fields>; }}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    main(sys.argv[1])
