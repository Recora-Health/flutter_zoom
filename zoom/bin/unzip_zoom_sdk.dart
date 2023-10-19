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
  var androidRTCLibFile = location + '/android/libs/mobilertc.aar';
  var iosSDKFile = location + '/ios/MobileRTC.xcframework/ios-arm64/MobileRTC.framework/MobileRTC';
  var iosSimulateSDKFile =
      location + '/ios/MobileRTC.xcframework/ios-i386_x86_64-simulator/MobileRTC.framework/MobileRTC';
  var iosSimulateArm64SDKFile = location +
      '/ios/MobileRTC.xcframework/ios-arm64_x86_64-simulator/MobileRTC.framework/MobileRTC';

  var exists = await File(androidCommonLibFile).exists();
  if (exists && isUpdate) {
    await File(androidCommonLibFile).delete();
  }
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/scl/fi/uqytqkxhdnkpd301h8bbi/commonlib.aar?rlkey=qkzawxgblv20vk6m9m0wg070v&dl=1'), androidCommonLibFile, isUpdate);
  }
  
  exists = await File(androidRTCLibFile).exists();
  if (exists && isUpdate) {
    await File(androidRTCLibFile).delete();
  }
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/scl/fi/h15xaempqwtnninzn870d/mobilertc.aar?rlkey=g09z68btzplixa2rnxiwhzjoo&dl=1'), androidRTCLibFile, isUpdate);
  }

  
  exists = await File(iosSDKFile).exists();
  if (exists && isUpdate) {
    await File(iosSDKFile).delete();
  }
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse('https://www.dropbox.com/scl/fi/sfyd8lkf2s4wmzkkz95qh/arm64-MobileRTC?rlkey=7d5k049phuyjjcs7fyqg3hn55&dl=1'), iosSDKFile, isUpdate);
  }

  exists = await File(iosSimulateSDKFile).exists();
  if (exists && isUpdate) {
    await File(iosSimulateSDKFile).delete();
  }
  // if (!exists || isUpdate) {
  //   await downloadFile(Uri.parse('https://www.dropbox.com/scl/fi/lt8s3od90ar8i76a3yag9/x86_64-simulator-MobileRTC?rlkey=3ereax8bqjetgao8zyfgwhqv6&dl=1'),
  //       iosSimulateSDKFile, isUpdate);
  // }


  exists = await File(iosSimulateArm64SDKFile).exists();
  if (exists && isUpdate) {
    await File(iosSimulateArm64SDKFile).delete();
  }
  if (!exists || isUpdate) {
    await downloadFile(
        Uri.parse(
            'https://www.dropbox.com/scl/fi/lt8s3od90ar8i76a3yag9/x86_64-simulator-MobileRTC?rlkey=3ereax8bqjetgao8zyfgwhqv6&dl=1'),
        iosSimulateArm64SDKFile,
        isUpdate);
  }
}

Future<void> downloadFile(Uri uri, String savePath, bool isUpdate) async {
  print('${isUpdate ? 'Updating' : 'Downloading'} ${uri.toString()} to $savePath');
  print(Directory.current.path);
  File destinationFile = await File(savePath).create(recursive: true);
  final request = await HttpClient().getUrl(uri);
  final response = await request.close();
  await response.pipe(destinationFile.openWrite());
}
