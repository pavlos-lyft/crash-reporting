package com.lyft.crasher

class NativeCrasher {

    external fun makeNativeCrash()

    external fun makeNativeAnr()

    companion object {

        init {
            System.loadLibrary("crasher")
        }
    }
}