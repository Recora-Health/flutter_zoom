package com.webcare.zoom;

import android.os.Handler;
import android.os.Looper;

import java.util.HashMap;
import java.util.Map;

import io.flutter.plugin.common.EventChannel;
import us.zoom.sdk.EnumComponentType;
import us.zoom.sdk.InMeetingService;
import us.zoom.sdk.MobileRTCNetworkQuality;
import us.zoom.sdk.ZoomSDK;

/**
 * Streams in-meeting network quality changes to Flutter.
 *
 * Forwards InMeetingServiceListener.onUserNetworkStatusChanged as a map:
 * {component: "audio"|"video"|..., quality: "verybad".."excellent"|"unknown",
 *  uplink: bool, userId: long}
 *
 * The SDK must be initialized before Dart subscribes (subscribe when joining a
 * meeting); a subscription made before init receives no events.
 */
public class QualityStreamHandler implements EventChannel.StreamHandler {
    private final Handler mainHandler = new Handler(Looper.getMainLooper());
    private InMeetingServiceListenerAdapter listener;

    @Override
    public void onListen(Object arguments, final EventChannel.EventSink events) {
        ZoomSDK zoomSDK = ZoomSDK.getInstance();
        if (!zoomSDK.isInitialized()) {
            return;
        }
        final InMeetingService inMeetingService = zoomSDK.getInMeetingService();
        if (inMeetingService == null) {
            return;
        }

        removeListener();
        listener = new InMeetingServiceListenerAdapter() {
            @Override
            public void onUserNetworkStatusChanged(EnumComponentType component, MobileRTCNetworkQuality quality,
                                                   long userId, boolean uplink) {
                final Map<String, Object> event = new HashMap<>();
                event.put("component", componentName(component));
                event.put("quality", qualityName(quality));
                event.put("uplink", uplink);
                event.put("userId", userId);

                if (Looper.myLooper() == Looper.getMainLooper()) {
                    events.success(event);
                } else {
                    mainHandler.post(() -> events.success(event));
                }
            }
        };
        inMeetingService.addListener(listener);
    }

    @Override
    public void onCancel(Object arguments) {
        removeListener();
    }

    private void removeListener() {
        if (listener == null) {
            return;
        }
        ZoomSDK zoomSDK = ZoomSDK.getInstance();
        if (zoomSDK.isInitialized()) {
            InMeetingService inMeetingService = zoomSDK.getInMeetingService();
            if (inMeetingService != null) {
                inMeetingService.removeListener(listener);
            }
        }
        listener = null;
    }

    private static String componentName(EnumComponentType component) {
        if (component == null) {
            return "unknown";
        }
        switch (component) {
            case EnumComponentType_AUDIO:
                return "audio";
            case EnumComponentType_VIDEO:
                return "video";
            case EnumComponentType_SHARE:
                return "share";
            case EnumComponentType_Chat:
                return "chat";
            case EnumComponentType_FT:
                return "file_transfer";
            default:
                return "default";
        }
    }

    private static String qualityName(MobileRTCNetworkQuality quality) {
        if (quality == null) {
            return "unknown";
        }
        switch (quality) {
            case MobileRTCNetworkQuality_VeryBad:
                return "verybad";
            case MobileRTCNetworkQuality_Bad:
                return "bad";
            case MobileRTCNetworkQuality_NotGood:
                return "notgood";
            case MobileRTCNetworkQuality_Normal:
                return "normal";
            case MobileRTCNetworkQuality_Good:
                return "good";
            case MobileRTCNetworkQuality_Excellent:
                return "excellent";
            default:
                return "unknown";
        }
    }
}
