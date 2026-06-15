package com.blueparrott.blueparrottsdk;

// No-op stub. mobilertc.aar references this interface via invokeinterface.
public interface BPHeadset {
    boolean connected();

    boolean valuesRead();

    boolean sdkModeEnabled();

    void enableSDKMode();

    void disableSDKMode();

    void connect(int mode);

    void addListener(IBPHeadsetListener listener);
}
