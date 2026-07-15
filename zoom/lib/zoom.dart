import 'dart:async';

import 'src/zoom_platform.dart';
export 'src/zoom_options.dart' show ZoomOptions, ZoomMeetingOptions;

class Zoom {
  Future<List> init(ZoomOptions options) async => ZoomPlatform.instance.initZoom(options);

  Future<bool> startMeeting(ZoomMeetingOptions options) async => ZoomPlatform.instance.startMeeting(options);

  Future<bool> joinMeeting(ZoomMeetingOptions options) async => ZoomPlatform.instance.joinMeeting(options);

  Future<List> meetingStatus() => ZoomPlatform.instance.meetingStatus();

  Stream<dynamic> get onMeetingStateChanged => ZoomPlatform.instance.onMeetingStatus();

  /// In-meeting network quality changes (onUserNetworkStatusChanged), as maps of
  /// {component: "audio"|"video"|"share", quality: "verybad"|"bad"|"notgood"|
  /// "normal"|"good"|"excellent"|"unknown", uplink: bool, userId: int}.
  /// Subscribe after init(), once a meeting is being joined.
  Stream<dynamic> get onNetworkQuality => ZoomPlatform.instance.onNetworkQuality();

  Future<void> leaveMeeting() async => ZoomPlatform.instance.leaveMeeting();
}
