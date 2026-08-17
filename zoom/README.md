# Flutter Zoom
A Flutter plugin for the Zoom Client SDK.

## Zoom SDK Versions

Android: zoom-sdk-android-6.6.9.35200
iOS: zoom-sdk-ios-6.6.9.29800

## ⚠️ iOS: pruned localizations — RE-APPLY ON EVERY SDK UPGRADE

`ios/MobileRTCResources.bundle` ships 19 `.lproj` folders upstream. We keep only the 10 that
overlap the Recora app's supported locales and have **deleted the other 9** to cut app download
size (9.2 MB uncompressed / **2.7 MiB** off the compressed App Store download):

    deleted: fr-CA  id  it  nl  pl  sv  tr  zh-Hans  zh-Hant
    kept:    de  en  es  fr  ja  ko  pt-BR  pt-PT  ru  vi

`flutter pub run zoom:unzip_zoom_sdk` does **not** restore these — it only fetches the
gitignored binaries (`mobilertc.aar`, `MobileRTC`). But **re-vendoring a new
`MobileRTCResources.bundle` during an SDK upgrade WILL bring all 19 back.** Re-delete the 9
above after any SDK bump, and re-check the keep-list against `lib/l10n/*.arb` in the app.

Safe to edit: the bundle is not code-signed (no `_CodeSignature`), so pruning does not
invalidate any signature. Zoom falls back to `en` for unlisted locales.

### Do NOT try to remove `zoomcml.xcframework` to save size

It looks optional (it only powers virtual backgrounds / filters / 3D avatars, which this app
never uses) but it is **not**. `MobileRTC` declares it as a hard, non-weak dependency:

    $ otool -l MobileRTC | grep -A2 zoomcml
              cmd LC_LOAD_DYLIB          # <- NOT LC_LOAD_WEAK_DYLIB
             name @rpath/zoomcml.framework/zoomcml

dyld resolves this at **process launch**, so dropping it crashes the app on start for every
user with `Library not loaded: @rpath/zoomcml.framework/zoomcml` — not a lazy failure when
someone opens virtual backgrounds. The 12 MB stays. (Force-weakening via
`install_name_tool -weak_library` rewrites a vendor binary, breaks its signature, and turns
internal calls into null-derefs — not acceptable here.)

## Installation from pub.dev
https://pub.dev/packages/zoom

After install the library, must run the follow script to get some sdk stuff for the first time:
```shell script
flutter pub run zoom:unzip_zoom_sdk
```
## Installation from github

```yaml
  zoom:
    git:
      url: git@github.com:driftboat/flutter_zoom.git
      ref: main
      path: zoom
```
After install the library, must run the follow script to get some sdk stuff for the first time:
```shell script
flutter pub run zoom:unzip_zoom_sdk
```

### iOS

Add two rows to the `ios/Runner/Info.plist`:

- one with the key `Privacy - Camera Usage Description` and a usage description.
- and one with the key `Privacy - Microphone Usage Description` and a usage description.

Or in text format add the key:

```xml
<key>NSCameraUsageDescription</key>
<string>Need to use the camera for call</string>
<key>NSMicrophoneUsageDescription</key>
<string>Need to use the microphone for call</string>
```


Diable BITCODE in the `ios/Podfile`:

```
post_install do |installer|
  installer.pods_project.targets.each do |target|
    flutter_additional_ios_build_settings(target)
    target.build_configurations.each do |config|
      config.build_settings['ENABLE_BITCODE'] = 'NO'
    end
  end
end
```

**NOTE for testing on the iOS simulator**

If you want to use the iOS Simulator to test your app, you will need to ensure you have the iOS Dev Zoom SDK as a dependency. 

To use the Dev Zoom SDK, run the following
```shell script
flutter pub run zoom:unzip_zoom_sdk dev
```
    
To switch back to the normal Zoom SDK, simply run

```shell script
flutter pub run zoom:unzip_zoom_sdk
```

### Android

Change the minimum Android sdk version to at the minimum 21 in your `android/app/build.gradle` file.

```
minSdkVersion 28
```

Update Material Design version to 1.5.0 in your `android/app/build.gradle` file.

```
implementation "com.google.android.material:material:1.5.0"
```


Disable shrinkResources for release buid
```
   buildTypes {
        release {
            // TODO: Add your own signing config for the release build.
            // Signing with the debug keys for now, so `flutter run --release` works.
            signingConfig signingConfigs.debug
            shrinkResources false 
            minifyEnabled false
        }
    }
```

### Web

Add stylesheet to the head of index.html
```html
<link type="text/css" rel="stylesheet" href="https://source.zoom.us/1.9.9/css/bootstrap.css" />
<link type="text/css" rel="stylesheet" href="https://source.zoom.us/1.9.9/css/react-select.css" />
```
Import ZoomMtg dependencies to the body of index.html
```html
<!-- import ZoomMtg dependencies -->
   <script src="https://source.zoom.us/1.9.9/lib/vendor/react.min.js"></script>
   <script src="https://source.zoom.us/1.9.9/lib/vendor/react-dom.min.js"></script>
   <script src="https://source.zoom.us/1.9.9/lib/vendor/redux.min.js"></script>
   <script src="https://source.zoom.us/1.9.9/lib/vendor/redux-thunk.min.js"></script>
   <script src="https://source.zoom.us/1.9.9/lib/vendor/lodash.min.js"></script>
   <script src="https://source.zoom.us/1.9.9/lib/av/1502_js_media.min.js"></script>

   <!-- import ZoomMtg -->
   <script src="https://source.zoom.us/zoom-meeting-1.9.9.min.js"></script>

   <script src="main.dart.js" type="application/javascript"></script>
```
Append "zmmtg-root" after zoom inited 
```dart
if (kIsWeb) {
    var zr = window.document.getElementById("zmmtg-root");
    querySelector('body').append(zr);
}
```

## example
- Auth zoom with "SDK App JWT Token"
  - Create SDK App JWT Token
    - Create SDK Key&Secret https://marketplace.zoom.us/docs/sdk/native-sdks/auth#key-secret-2
    - Generate JWT Token from https://jwt.io/ for testing. （Get it from your server for distribution，You can get current timestamp from https://www.unixtimestamp.com/. ）   
      Replace "PAYLOAD" as bellow, Enter your "SDK Secret" in "your-256-bit-secret",Get  "your jwtToken" from the left. 
      
      ```
      {
        "appKey": "string", // Your SDK key
        "iat": long, // access token issue timestamp
        "exp": long, // access token expire timestamp (The exp should be later than or equal to tokenExp)
        "tokenExp": long // should be a timestamp that is at least 30 minutes later than the iat)
      }
      ```
      PAYLOAD Example：  
      ```
      {
        "appKey": "xxxxxxxxxxxxxxxxxxxx", 
        "iat": 1615510799, 
        "exp": 1647017999, 
        "tokenExp": 1647017999 
      }
      ```
  -  replace "your jwtToken" in "zoom/example/lib/join_screen.dart"
  
- If you don't want use jwtToken, You can Auth zoom with "SDK App Key&Secret"
  - Comment out "your jwtToken" and Uncomment "appKey&appSecret", it should be like this:  
  ```
  ZoomOptions zoomOptions = new ZoomOptions(
      domain: "zoom.us",
      //https://marketplace.zoom.us/docs/sdk/native-sdks/auth
      //https://jwt.io/
      //--todo from server
      //jwtToken: "your jwtToken",
      appKey: "appKey", // Replace with with key got from the Zoom Marketplace ZOOM SDK Section
      appSecret: "appSecret", // Replace with with secret got from the Zoom Marketplace ZOOM SDK Section
    );
  ```
      



# reference
https://github.com/decodedhealth/flutter_zoom_plugin
