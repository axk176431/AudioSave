package com.example.audiosave;

public enum AudioEngine {

    INSTANCE;

    // load native library
    static {
        System.loadLibrary("native-lib");
    }

    // Native methods
    public static native void create(int inputDeviceId, int inputChannelCount);
    public static native void start();
    public static native void stop();
    public static native void delete();
}
