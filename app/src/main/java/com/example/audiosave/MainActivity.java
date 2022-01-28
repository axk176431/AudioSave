package com.example.audiosave;

import android.Manifest;
import android.os.Bundle;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends PermissionActivity {

    private static final String TAG = MainActivity.class.getName();

    private static final String[] PERMISSIONS = {
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    private Button mButton;

    private boolean isOn = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // keep screen on all the time
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // setup button
        mButton = findViewById(R.id.button);
        mButton.setSoundEffectsEnabled(false);
        mButton.setOnClickListener(view -> {
            isOn = !isOn;
            if (isOn) {
                mButton.setText(R.string.stop_button);
                startAudioEngine();
            } else {
                mButton.setText(R.string.start_button);
                stopAudioEngine();
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();

        // check for permissions when app resumes
        checkPermissions(PERMISSIONS);
    }

    @Override
    protected void onPause() {
        super.onPause();
        stopAudioEngine();
    }

    private void startAudioEngine() {
        PreferredMic mic = PreferredMic.get(this);
        AudioEngine.create(mic.getId(), mic.getChannelCount());
        AudioEngine.start();
    }

    private void stopAudioEngine() {
        AudioEngine.stop();
        AudioEngine.delete();
    }

    @Override
    protected void onPermissionsNotGranted(String[] missingPermissions) {
        Toast.makeText(this, R.string.permissions_not_granted, Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onPermissionsGranted() {
        // do nothing
    }
}