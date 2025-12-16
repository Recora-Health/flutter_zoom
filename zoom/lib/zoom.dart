import 'dart:async';

import 'src/zoom_platform.dart';
export 'src/zoom_options.dart' show ZoomOptions, ZoomMeetingOptions;

class Zoom {
  Future<List> init(ZoomOptions options) async => ZoomPlatform.instance.initZoom(options);

  Future<bool> startMeeting(ZoomMeetingOptions options) async => ZoomPlatform.instance.startMeeting(options);

  Future<bool> joinMeeting(ZoomMeetingOptions options) async => ZoomPlatform.instance.joinMeeting(options);

  Future<List> meetingStatus() => ZoomPlatform.instance.meetingStatus();

  Stream<dynamic> get onMeetingStateChanged => ZoomPlatform.instance.onMeetingStatus();

  Future<void> leaveMeeting() async => ZoomPlatform.instance.leaveMeeting();
}
