package com.reactnativefastfs;

import androidx.annotation.NonNull;
import android.util.Log;

import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = FastFsModule.NAME)
public class FastFsModule extends ReactContextBaseJavaModule {
    public static final String NAME = "FastFs";

    public FastFsModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    @NonNull
    public String getName() {
        return NAME;
    }

    @ReactMethod(isBlockingSynchronousMethod = true)
    public boolean install() {
        try {
            Log.i(NAME, "Loading C++ library...");
            System.loadLibrary("reactnativefastfs");

            JavaScriptContextHolder jsContext = getReactApplicationContext().getJavaScriptContextHolder();
            nativeInstall(jsContext.get());
            Log.i(NAME, "Successfully installed MMKV JSI Bindings!");
            return true;
        } catch (Exception exception) {
            Log.e(NAME, "Failed to install MMKV JSI Bindings!", exception);
            return false;
        }
    }

    private static native void nativeInstall(long jsiPtr);
}
