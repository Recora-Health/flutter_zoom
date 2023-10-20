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
    location = zoomFileUri;
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
  // The commonlib.aar and mobilertc.aar are the same for all architectures
  // The MobileRTC.framework is different for each architecture, device vs emulator
  // The iosSimulateSDKFile is depreciated and will be removed when isUpdate is true
  var androidCommonLibFile = location + '/android/libs/commonlib.aar';
  var androidRTCLibFile = location + '/android/libs/mobilertc.aar';
  var iosSDKFile = location + '/ios/MobileRTC.xcframework/ios-arm64/MobileRTC.framework/MobileRTC';
  var iosSimulateSDKFile =
      location + '/ios/MobileRTC.xcframework/ios-i386_x86_64-simulator/MobileRTC.framework/MobileRTC';
  var iosSimulateArm64SDKFile = location +
      '/ios/MobileRTC.xcframework/ios-arm64_x86_64-simulator/MobileRTC.framework/MobileRTC';

  // Check if the Android Common SDK files exist
  var exists = await File(androidCommonLibFile).exists();
  // If the files exist and we are updating, then delete the previous version
  if (exists && isUpdate) {
    await File(androidCommonLibFile).delete();
  }
  // If the files do not exist or we are updating, then download the latest version
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/scl/fi/s2j0drth0446ukpl2xsht/commonlib.aar?rlkey=94lfhuk6smdtyn43nazvtk2go&dl=1'), androidCommonLibFile, isUpdate);
  }
  
  // Check if the Android MobileRTC SDK files exist
  exists = await File(androidRTCLibFile).exists();
  // If the files exist and we are updating, then delete the previous version
  if (exists && isUpdate) {
    await File(androidRTCLibFile).delete();
  }
  // If the files do not exist or we are updating, then download the latest version
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/scl/fi/memra2091eqf54rxebc78/mobilertc.aar?rlkey=xvwrdsdm8jltk8f0hyss5yfpd&dl=1'), androidRTCLibFile, isUpdate);
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
        Uri.parse('https://www.dropbox.com/scl/fi/d1uk5j6am2bepbvcpl7vv/arm64-MobileRTC?rlkey=c0rw3tnrsvxhy4w0ypnvpty0w&dl=1'), iosSDKFile, isUpdate);
  }

  //  Check if the i386 iOS Emulator SDK files exist
  exists = await File(iosSimulateSDKFile).exists();
  // If the files exist and we are updating, then delete the previous version
  if (exists && isUpdate) {
    await File(iosSimulateSDKFile).delete();
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
            'https://www.dropbox.com/scl/fi/4hujrxquahtej4fwz0j2o/x86_64-simulator-MobileRTC?rlkey=nrvjqy8ocp8r80ahpkn697pvb&dl=1'),
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
}
