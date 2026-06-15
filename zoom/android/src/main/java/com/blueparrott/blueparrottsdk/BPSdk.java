package com.blueparrott.blueparrottsdk;

import android.content.Context;

// No-op stub. Zoom's JabraDeviceManager calls BPSdk.getBPHeadset(context) and then
// invokes methods on the returned BPHeadset without null-checking, so we must
// return a non-null no-op singleton rather than null.
public class BPSdk {
    private static final BPHeadset NO_OP_HEADSET = new NoOpHeadset();

    public static void setRemoteLogging(boolean enabled) {
    }

    public static BPHeadset getBPHeadset(Context context) {
        return NO_OP_HEADSET;
    }

    private static final class NoOpHeadset implements BPHeadset {
        @Override
        public boolean connected() {
            return false;
        }

        @Override
        public boolean valuesRead() {
            return false;
        }

        @Override
        public boolean sdkModeEnabled() {
            return false;
        }

        @Override
        public void enableSDKMode() {
        }

        @Override
        public void disableSDKMode() {
        }

        @Override
        public void connect(int mode) {
        }

        @Override
        public void addListener(IBPHeadsetListener listener) {
        }
    }
}
