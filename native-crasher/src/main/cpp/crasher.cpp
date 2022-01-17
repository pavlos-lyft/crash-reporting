#include <jni.h>
#include <string>
#include <csignal>

extern "C" {

// ===== makeNativeCrash =====

static void __attribute__((used)) nonOptimizedFunc(void) {}

int makeCrashImpl() {
    volatile char *ptr = (char *) nonOptimizedFunc;
    *ptr = 0;

    return 42;
}


JNIEXPORT void JNICALL
Java_com_lyft_crasher_NativeCrasher_makeNativeCrash(JNIEnv *env, jobject) {
    makeCrashImpl();
}

// ===== makeNativeAnr =====

volatile unsigned nonOptimizedVar;

_Noreturn void makeAnrImpl() {
    for (unsigned int i = 0;; i++) {
        nonOptimizedVar = i;
    }
}

JNIEXPORT void JNICALL
Java_com_lyft_crasher_NativeCrasher_makeNativeAnr(JNIEnv *env, jobject) {
    makeAnrImpl();
}

}