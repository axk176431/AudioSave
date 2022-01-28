package com.example.audiosave;

import android.content.Context;
import android.media.AudioDeviceInfo;
import android.media.AudioManager;

public class PreferredMic {

    private final int id;
    private final int channelCount;
    private static PreferredMic mPreferredMic;

    private PreferredMic(final int id, final int channelCount) {
        this.id = id;
        this.channelCount = channelCount;
    }

    public static PreferredMic get(final Context context) {
        if (mPreferredMic == null) {
            findBest(context);
        }
        return mPreferredMic;
    }

    private static void findBest(final Context context) {
        AudioManager audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
        assert audioManager != null;
        AudioDeviceInfo[] inputDevices = audioManager.getDevices(AudioManager.GET_DEVICES_INPUTS);
        int deviceId = 0;
        int channelCount = 1;
        for (AudioDeviceInfo curr : inputDevices) {
            if (curr.getType() == AudioDeviceInfo.TYPE_BUILTIN_MIC) {
                int n = curr.getChannelCounts().length;
                if (n != 0 && curr.getChannelCounts()[n - 1] >= channelCount) {
                    channelCount = curr.getChannelCounts()[n - 1];
                    deviceId = curr.getId();

                }
            }
        }
        mPreferredMic = new PreferredMic(deviceId, channelCount);
    }

    public int getId() {
        return id;
    }

    public int getChannelCount() {
        return channelCount;
    }
}