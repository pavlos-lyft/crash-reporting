#include <jni.h>
#include <csignal>
#include <fstream>

#include "bugsnag.h"
#include "crash_interceptor.h"

extern "C" {

JNIEXPORT void JNICALL
Java_com_lyft_android_crashreporting_NdkCrashReporting_performNativeBugsnagSetup(
        JNIEnv *env, jobject instance, jstring _workingDir, jboolean sendEventsToBugsnag, jboolean cacheEvents,
        jint cacheFileCharLimit) {

    const char *workingDir = env->GetStringUTFChars(_workingDir, nullptr);
    setupCrashInterceptor(workingDir, (bool) sendEventsToBugsnag, (bool) cacheEvents, (int) cacheFileCharLimit);
}

}