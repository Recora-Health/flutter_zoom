package com.webcare.zoom;

import android.content.Context;

import androidx.annotation.NonNull;

import java.util.Arrays;
import java.util.List;
import java.util.Map;

import io.flutter.embedding.engine.plugins.FlutterPlugin;
import io.flutter.embedding.engine.plugins.activity.ActivityPluginBinding;
import io.flutter.plugin.common.EventChannel;
import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;
import us.zoom.sdk.SDKNotificationServiceError;
import us.zoom.sdk.JoinMeetingOptions;
import us.zoom.sdk.JoinMeetingParams;
import us.zoom.sdk.MeetingService;
import us.zoom.sdk.MeetingSettingsHelper;
import us.zoom.sdk.MeetingStatus;
import us.zoom.sdk.StartMeetingOptions;
import us.zoom.sdk.StartMeetingParamsWithoutLogin;
import us.zoom.sdk.ZoomError;
import us.zoom.sdk.ZoomSDK;
import us.zoom.sdk.ZoomSDKAuthenticationListener;
import us.zoom.sdk.ZoomSDKInitParams;
import us.zoom.sdk.ZoomSDKInitializeListener;
import us.zoom.sdk.ZoomSDKRawDataMemoryMode;
import io.flutter.embedding.engine.plugins.activity.ActivityAware;

/** ZoomPlugin */
public class ZoomPlugin implements FlutterPlugin, MethodCallHandler,ActivityAware, ZoomSDKAuthenticationListener {
    /// The MethodChannel that will the communication between Flutter and native Android
    ///
    /// This local reference serves to register the plugin with the Flutter Engine and unregister it
    /// when the Flutter Engine is detached from the Activity
    private MethodChannel channel;
    private EventChannel meetingStatusChannel;
    private Context context;
    @Override
    public void onAttachedToEngine(@NonNull FlutterPluginBinding flutterPluginBinding) {
        context = flutterPluginBinding.getApplicationContext();
        channel = new MethodChannel(flutterPluginBinding.getBinaryMessenger(), "plugins.webcare/zoom_channel");
        channel.setMethodCallHandler(this);

        meetingStatusChannel = new EventChannel(flutterPluginBinding.getBinaryMessenger(), "plugins.webcare/zoom_event_stream");
    }

    @Override
    public void onMethodCall(@NonNull MethodCall call, @NonNull Result result) {
        switch (call.method) {
            case "init":
                init(call, result);
                break;
            case "join":
                joinMeeting(call, result);
                break;
            case "meeting_status":
                meetingStatus(result);
                break;
            case "leave":
                leave(result);
                break;
            default:
                result.notImplemented();
        }
    }

    @Override
    public void onDetachedFromEngine(@NonNull FlutterPluginBinding binding) {
        channel.setMethodCallHandler(null);
    }

    private void init(final MethodCall methodCall, final MethodChannel.Result result) {

        Map<String, String> options = methodCall.arguments();

        ZoomSDK zoomSDK = ZoomSDK.getInstance();

        if(zoomSDK.isInitialized()) {
            List<Integer> response = Arrays.asList(0, 0);
            result.success(response);
            return;
        }

        ZoomSDKInitParams initParams = new ZoomSDKInitParams();
        initParams.domain = options.get("domain");
        if(options.containsKey("jwtToken")){
            initParams.jwtToken = options.get("jwtToken");
        }

        zoomSDK.initialize(
                context,
                new ZoomSDKInitializeListener() {

                    @Override
                    public void onZoomAuthIdentityExpired() {

                    }

                    @Override
                    public void onZoomSDKInitializeResult(int errorCode, int internalErrorCode) {
                        List<Integer> response = Arrays.asList(errorCode, internalErrorCode);

                        if (errorCode != ZoomError.ZOOM_ERROR_SUCCESS) {
                            System.out.println("ZoomMeeting: Failed to initialize Zoom SDK");
                            result.success(response);
                            return;
                        }

                        ZoomSDK zoomSDK = ZoomSDK.getInstance();
                        MeetingService meetingService = zoomSDK.getMeetingService();
                        meetingStatusChannel.setStreamHandler(new StatusStreamHandler(meetingService));

                        // Set custom meeting UI activity for edge-to-edge support on Android 16
                        // Use reflection to load the app's custom activity class
                        try {
                            Class<?> customActivityClass = Class.forName(
                                "com.recorahealth.members.ZoomMeetingActivity"
                            );
                            // Cast to the expected type for setNewMeetingUI
                            @SuppressWarnings("unchecked")
                            Class<? extends us.zoom.sdk.NewMeetingActivity> activityClass =
                                (Class<? extends us.zoom.sdk.NewMeetingActivity>) customActivityClass;
                            zoomSDK.getZoomUIService().setNewMeetingUI(activityClass);
                            System.out.println("ZoomMeeting: Custom Zoom meeting UI set successfully");
                        } catch (ClassNotFoundException e) {
                            System.out.println("ZoomMeeting: Custom activity class not found: " + e.getMessage());
                        } catch (Exception e) {
                            System.out.println("ZoomMeeting: Failed to set custom meeting UI: " + e.getMessage());
                            e.printStackTrace();
                        }

                        result.success(response);
                    }
                },
                initParams);
    }

    private void joinMeeting(MethodCall methodCall, MethodChannel.Result result) {

        Map<String, String> options = methodCall.arguments();

        ZoomSDK zoomSDK = ZoomSDK.getInstance();

        if(!zoomSDK.isInitialized()) {
            System.out.println("ZoomMeeting: Not initialized!!!!!!");
            result.success(false);
            return;
        }

        JoinMeetingOptions opts = new JoinMeetingOptions();
        opts.no_invite = parseBoolean(options, "disableInvite", false);
        opts.no_share = parseBoolean(options, "disableShare", false);
        opts.no_driving_mode =  parseBoolean(options, "disableDrive", false);
        opts.no_dial_in_via_phone =  parseBoolean(options, "disableDialIn", false);
        opts.no_disconnect_audio =  parseBoolean(options, "noDisconnectAudio", false);
        opts.no_audio = parseBoolean(options, "noAudio", false);
        opts.no_video = parseBoolean(options, "noVideo", false);
        opts.no_share =  parseBoolean(options, "noShare", false);
        opts.no_meeting_chat = parseBoolean(options, "disableChat", false);
        opts.meeting_views_options = parseInt(options, "meetingViewOptions", 0);
        opts.no_meeting_end_message = parseBoolean(options, "noMeetingEndMessage", false);
        opts.no_titlebar = parseBoolean(options, "noTitlebar", false);
        opts.no_bottom_toolbar = parseBoolean(options, "noBottomToolbar", false);
        opts.no_dial_out_to_phone = parseBoolean(options, "noDialOut", false);
        opts.no_record = parseBoolean(options, "noRecord", false);
        opts.no_meeting_error_message = parseBoolean(options, "noMeetingErrorMessage", false); 

        JoinMeetingParams params = new JoinMeetingParams();

        params.displayName = options.get("userId");
        params.meetingNo = options.get("meetingId");
        params.password = options.get("meetingPassword");
        params.webinarToken = options.get("webToken");

        final MeetingService meetingService = zoomSDK.getMeetingService();

        final MeetingSettingsHelper meetingSettingsHelper = zoomSDK.getMeetingSettingsHelper();
        // Configure settings before joining - using non-deprecated methods
        meetingSettingsHelper.enable720p(false);
        meetingSettingsHelper.enableShowMyMeetingElapseTime(true);

        // Join the meeting with the configured options
        meetingService.joinMeetingWithParams(context, params, opts);

        result.success(true);
    }

    private boolean parseBoolean(Map<String, String> options, String property, boolean defaultValue) {
        return options.get(property) == null ? defaultValue : Boolean.parseBoolean(options.get(property));
    }

    private int parseInt(Map<String, String> options, String property, int defaultValue) {
        return options.get(property) == null ? defaultValue : Integer.parseInt(options.get(property));
    }


    private void meetingStatus(MethodChannel.Result result) {

        ZoomSDK zoomSDK = ZoomSDK.getInstance();

        if(!zoomSDK.isInitialized()) {
            System.out.println("ZoomMeeting: Not initialized!!!!!!");
            result.success(Arrays.asList("MEETING_STATUS_UNKNOWN", "SDK not initialized"));
            return;
        }

        MeetingService meetingService = zoomSDK.getMeetingService();

        if(meetingService == null) {
            result.success(Arrays.asList("MEETING_STATUS_UNKNOWN", "No status available"));
            return;
        }

        MeetingStatus status = meetingService.getMeetingStatus();
        result.success(status != null ? Arrays.asList(status.name(), "") :  Arrays.asList("MEETING_STATUS_UNKNOWN", "No status available"));
    }

    private void leave(MethodChannel.Result result) {

        ZoomSDK zoomSDK = ZoomSDK.getInstance();

        if(!zoomSDK.isInitialized()) {
            System.out.println("ZoomMeeting: Not initialized!!!!!!");
            result.success(Arrays.asList("MEETING_STATUS_UNKNOWN", "SDK not initialized"));
            return;
        }

        MeetingService meetingService = zoomSDK.getMeetingService();

        if(meetingService == null) {
            result.success(Arrays.asList("MEETING_STATUS_UNKNOWN", "No status available"));
            return;
        }

        meetingService.leaveCurrentMeeting(true);
        result.success(true);
    }

    @Override
    public void onZoomAuthIdentityExpired() {

    }

    @Override
    public void onZoomSDKLoginResult(long result) {

    }

    @Override
    public void onZoomSDKLogoutResult(long result) {

    }

    @Override
    public void onZoomIdentityExpired() {

    }

    @Override
    public void onAttachedToActivity(@NonNull ActivityPluginBinding binding) {

    }

    @Override
    public void onDetachedFromActivityForConfigChanges() {

    }

    @Override
    public void onReattachedToActivityForConfigChanges(@NonNull ActivityPluginBinding binding) {

    }

    @Override
    public void onDetachedFromActivity() {

    }
}
