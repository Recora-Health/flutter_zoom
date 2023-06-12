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
  var androidCommonLibFile = location + '/android/libs/commonlib.aar';
  var exists = await File(androidCommonLibFile).exists();
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/s/wimmggu7tjnbr4w/commonlib.aar?dl=1'), androidCommonLibFile, isUpdate);
  }
  var androidRTCLibFile = location + '/android/libs/mobilertc.aar';
  exists = await File(androidRTCLibFile).exists();
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/s/p6q40yw4akvyimx/mobilertc.aar?dl=1'), androidRTCLibFile, isUpdate);
  }

  var iosSDKFile = location + '/ios/MobileRTC.xcframework/ios-arm64_armv7/MobileRTC.framework/MobileRTC';
  exists = await File(iosSDKFile).exists();

  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/s/zdzfl0ick5wdogo/arm64-MobileRTC?dl=1'), iosSDKFile, isUpdate);
  }

  var iosSimulateSDKFile =
      location + '/ios/MobileRTC.xcframework/ios-i386_x86_64-simulator/MobileRTC.framework/MobileRTC';
  exists = await File(iosSimulateSDKFile).exists();
  if (!exists || isUpdate) {
    await downloadFile(Uri.parse('https://www.dropbox.com/s/2t3u21bn9zatyb6/x86_64-simulator-MobileRTC?dl=1'),
        iosSimulateSDKFile, isUpdate);
  }
}

Future<void> downloadFile(Uri uri, String savePath, bool isUpdate) async {
  print('${isUpdate ? 'Updating' : 'Downloading'} ${uri.toString()} to $savePath');
  File destinationFile = await File(savePath).create(recursive: true);
  final request = await HttpClient().getUrl(uri);
  final response = await request.close();
  await response.pipe(destinationFile.openWrite());
}
