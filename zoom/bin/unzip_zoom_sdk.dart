import 'dart:core';
import 'dart:io';
import 'dart:convert';
import 'package:args/args.dart';

void main(List<String> args) async {
  final parser = ArgParser()..addFlag('update', negatable: false, abbr: 'u');
  final results = parser.parse(args);
  final isUpdate = results['update'] as bool;

  var location = Platform.script.toString();
  var isNewFlutter = location.contains(".snapshot");
  if (isNewFlutter) {
    var sp = Platform.script.toFilePath();
    var sd = sp.split(Platform.pathSeparator);
    sd.removeLast();
    var scriptDir = sd.join(Platform.pathSeparator);
    var packageConfigPath = [scriptDir, '..', '..', '..', 'package_config.json'].join(Platform.pathSeparator);
    var jsonString = File(packageConfigPath).readAsStringSync();
    Map<String, dynamic> packages = jsonDecode(jsonString);
    var packageList = packages["packages"];
    String? zoomFileUri;
    for (var package in packageList) {
      if (package["name"] == "zoom") {
        zoomFileUri = package["rootUri"];
        break;
      }
    }
    if (zoomFileUri == null) {
      print("zoom package not found!");
      return;
    }
    // rootUri is relative (e.g. "../../../flutter_zoom/zoom") when the app
    // consumes this package via a `path:` dependency; resolve it against the
    // package_config.json location so the SDK lands inside this package
    // instead of a mirrored directory next to the app.
    final packageConfigUri = Uri.file(File(packageConfigPath).absolute.path);
    location = packageConfigUri.resolve(zoomFileUri).toString();
    if (location.endsWith('/')) location = location.substring(0, location.length - 1);
  }
  if (Platform.isWindows) {
    location = location.replaceFirst("file:///", "");
  } else {
    location = location.replaceFirst("file://", "");
  }
  if (!isNewFlutter) location = location.replaceFirst("/bin/unzip_zoom_sdk.dart", "");

  await checkAndDownloadSDK(location, isUpdate);
  print('Complete');
}

Future<void> checkAndDownloadSDK(String location, bool isUpdate) async {
  // Setup the SDK destinations
  // The mobilertc.aar are the same for all architectures
  // The MobileRTC.framework is different for each architecture, device vs emulator
  var androidRTCLibFile = location + '/android/libs/mobilertc.aar';
  var iosSDKFile = location + '/ios/MobileRTC.xcframework/ios-arm64/MobileRTC.framework/MobileRTC';
  var iosSimulateArm64SDKFile = location +
      '/ios/MobileRTC.xcframework/ios-arm64-simulator/MobileRTC.framework/MobileRTC';
  
  // Check if the Android MobileRTC SDK files exist
  var exists = await File(androidRTCLibFile).exists();
  // If the files exist and we are updating, then delete the previous version
  if (exists && isUpdate) {
    await File(androidRTCLibFile).delete();
  }
  // If the files do not exist or we are updating, then download the latest version
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/scl/fi/r07z4g5g2yaq6cvprblyc/mobilertc.aar?rlkey=srfkfw7f3qj5uniuyn5ycjllc&st=mqezdx1r&dl=1'), androidRTCLibFile, isUpdate);
  }

  // Check if the iOS MobileRTC SDK files exist
  exists = await File(iosSDKFile).exists();
  // If the files exist and we are updating, then delete the previous version
  if (exists && isUpdate) {
    await File(iosSDKFile).delete();
  }
  // If the files do not exist or we are updating, then download the latest version
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/scl/fi/rt76vpdtl6hei1l9gs0ve/arm64-MobileRTC?rlkey=107nm6v687ryr8u9xn4omhykl&st=2tvx2ns3&dl=1'), iosSDKFile, isUpdate);
  }

  // Check if the Arm64 iOS Embulator SDK files exist
  exists = await File(iosSimulateArm64SDKFile).exists();
  // If the files exist and we are updating, then delete the previous version
  if (exists && isUpdate) {
    await File(iosSimulateArm64SDKFile).delete();
  }
  // If the files do not exist or we are updating, then download the latest version
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse(
            'https://www.dropbox.com/scl/fi/hq5t7a3b71f5fiiffbode/x86_64-simulator-MobileRTC?rlkey=tkimddj36agxxeqkvhn43enqu&st=qk8l5dz1&dl=1'),
        iosSimulateArm64SDKFile,
        isUpdate);
  }
}

Future<void> downloadFile(Uri uri, String savePath, bool isUpdate) async {
  print('${isUpdate ? 'Updating' : 'Downloading'} ${uri.toString()} to $savePath');
  File destinationFile = await File(savePath).create(recursive: true);
  final request = await HttpClient().getUrl(uri);
  final response = await request.close();
  await response.pipe(destinationFile.openWrite());
  // force update
}
