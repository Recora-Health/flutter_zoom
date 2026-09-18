## 3.0.1
* Android: support Gradle 9.3.1 / AGP 9.1.0 / KGP 2.4.0 (Flutter 3.47.4) with the AGP 9 opt-outs `android.newDsl=false` and `android.builtInKotlin=false`; modern `compileSdk`/`minSdk`/`buildFeatures`/`lint` DSL; Kotlin stdlib aligned to 2.4.0
* Android: the global R8 options (`-dontoptimize`, `-dontobfuscate`, `-optimizations`) are removed from the consumer proguard rules (AGP 9 rejects them) and must now be set in the host app's `proguard-rules.pro`
* Android: removed the unused `libs/build.gradle` and the library manifest's versionCode/versionName/installLocation
* iOS: podspec platform raised to iOS 15.0 (MobileRTC 7.0.5 minimum); simulator builds exclude `i386 x86_64` since the xcframeworks ship arm64 slices only
* Zoom Meeting SDK stays at 7.0.5

## 2.0.0
* BREAKING: Unified zoom_platform_interface into main zoom package
* Removed Git URL dependency, resolving gradle cache issues
* Internal restructuring: platform interface moved to src/ directory
* Public API remains unchanged (Zoom, ZoomOptions, ZoomMeetingOptions)
* No code changes required for users importing 'package:zoom/zoom.dart'

## 1.0.3+6
* add leave meeting command

## 1.0.3+5
* add meetingViewOptions to ZoomMeetingOptions(Android&iOS)

## 1.0.3+4
* add meetingViewOptions to ZoomMeetingOptions(Android Only)

## 1.0.3+3
* zoom install bug fixed

## 1.0.3+2
* zoom install bug fixed for flutter 2.8.0

## 1.0.3+1
* zoom_web to 1.0.2+1
* zoom web example updated

## 1.0.3
* zoom-sdk-android-5.7.1.1268
* zoom-sdk-ios-5.7.1.645
* jwtToken to optional,add back "AppKey&AppSecrect"

## 1.0.2+2
* folders("ios-sdk" and "android/libs")  missing bug fixed

## 1.0.2+1
* zoom_platform_interface to 1.0.2
* zoom_web to 1.0.2

## 1.0.2
* To published version, download sdk files from github

## 1.0.1
* zoom_platform_interface to 1.0.1
* zoom_web to 1.0.1

## 1.0.0

* init
