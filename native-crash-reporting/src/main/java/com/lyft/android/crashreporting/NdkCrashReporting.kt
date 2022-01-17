package com.lyft.android.crashreporting

class NdkCrashReporting {

    external fun performNativeBugsnagSetup(
        workingDir: String,
        sendEventsToBugsnag: Boolean,
        cacheEvents: Boolean,
        cacheFileCharLimit: Int
    )

    companion object {
        init {
            System.loadLibrary("crashreporting")
        }
    }
}