#ifndef CRASH_INTERCEPTOR_H
#define CRASH_INTERCEPTOR_H

#include "bugsnag.h"

void setupCrashInterceptor(const char *workingDir, bool sendEventsToBugsnag, bool cacheEvents, int cacheFileCharLimit);

#endif // CRASH_INTERCEPTOR_H
