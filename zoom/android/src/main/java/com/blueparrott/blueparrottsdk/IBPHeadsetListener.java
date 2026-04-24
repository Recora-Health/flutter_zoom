package com.blueparrott.blueparrottsdk;

// No-op stub so the Zoom SDK's jabra.* classes can resolve their superinterfaces
// at runtime without the real BlueParrott SDK being bundled.
// See: zoom/android/proguard.cfg and the plan in plans/this-is-not-a-dapper-brooks.md
public interface IBPHeadsetListener {
    void onConnectProgress(int progressCode);

    void onConnect();

    void onConnectFailure(int errorCode);

    void onDisconnect();

    void onModeUpdate();

    void onModeUpdateFailure(int errorCode);

    void onButtonDown(int buttonId);

    void onButtonUp(int buttonId);

    void onTap(int buttonId);

    void onDoubleTap(int buttonId);

    void onLongPress(int buttonId);

    void onProximityChange(int value);

    void onHeadsetLogChange(String message);

    void onValuesRead();

    void onEnterpriseValuesRead();
}
