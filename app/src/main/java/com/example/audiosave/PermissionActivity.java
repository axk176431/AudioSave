package com.example.audiosave;

import android.content.pm.PackageManager;

import java.util.ArrayList;
import java.util.List;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

public abstract class PermissionActivity extends AppCompatActivity {

    private static final int PERMISSIONS_REQUEST_CODE = 0;

    protected abstract void onPermissionsNotGranted(final String[] missingPermissions);
    protected abstract void onPermissionsGranted();

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        if (requestCode != PERMISSIONS_REQUEST_CODE) {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
        else if (grantResults.length < 1) {
            onPermissionsNotGranted(permissions);
        } else {
            List<String> missingPermissions = new ArrayList<>();
            boolean allPermissionsGranted = true;
            for (int i = 0; i < grantResults.length; i++) {
                if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                    allPermissionsGranted = false;
                    missingPermissions.add(permissions[i]);
                }
            }
            if (allPermissionsGranted) {
                onPermissionsGranted();
            } else {
                onPermissionsNotGranted(missingPermissions.toArray(new String[0]));
            }
        }
    }

    protected void checkPermissions(final String[] permissions) {
        List<String> pendingPermissions = new ArrayList<>();
        for (String permission: permissions) {
            int result = ActivityCompat.checkSelfPermission(this, permission);
            if (result != PackageManager.PERMISSION_GRANTED) {
                pendingPermissions.add(permission);
            }
        }
        if (pendingPermissions.isEmpty()) {
            onPermissionsGranted();
        } else {
            ActivityCompat.requestPermissions(
                    this,
                    pendingPermissions.toArray(new String[0]),
                    PERMISSIONS_REQUEST_CODE);
        }
    }
}
