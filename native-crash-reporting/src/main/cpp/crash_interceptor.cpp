#include "crash_interceptor.h"

#include <string>
#include <fstream>
#include <chrono>

#define CRASH_STACK_TRACE_MAX_LENGTH 2000
#define LOG_FILE_NAME "stacktrace"
#define LOG_FILE_EXT ".log"

std::string workingDir;
bool sendEventsToBugsnag;
bool cacheEvents;
int cacheFileCharLimit = CRASH_STACK_TRACE_MAX_LENGTH;

std::chrono::milliseconds currentTimeMillis() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
    );
}

bool canWriteMore(std::ofstream &stream) {
    int filePos = stream.tellp();
    return filePos < cacheFileCharLimit;
}

bool onError(void *event) {
    if (!cacheEvents) return sendEventsToBugsnag;

    auto currentTimeMs = std::to_string(currentTimeMillis().count());
    auto fileName = LOG_FILE_NAME + currentTimeMs + LOG_FILE_EXT;

    try {
        std::ofstream stream(workingDir + fileName);

        if (stream.good()) {
            stream << bugsnag_error_get_error_class(event) << std::endl;
            stream << bugsnag_error_get_error_message(event) << std::endl;

            for (int i = 0; i < bugsnag_event_get_stacktrace_size(event); i++) {
                if (!canWriteMore(stream)) break;

                bugsnag_stackframe *frame = bugsnag_event_get_stackframe(event, i);

                if (strlen(frame->filename) > 0) {
                    stream << frame->filename << ":" << frame->line_number;
                } else {
                    stream << "unknown";
                }
                stream << " ";

                if (!canWriteMore(stream)) break;

                if (strlen(frame->method) > 0) {
                    stream << frame->method;
                } else {
                    stream << (unsigned long *) frame->frame_address;
                }
                stream << std::endl;
            }
            stream.close();
        }
    } catch (std::ios_base::failure &e) {

    }
    return sendEventsToBugsnag;
}

void setupCrashInterceptor(const char *_workingDir, bool _sendEventsToBugsnag, bool _cacheEvents, int _cacheFileCharLimit) {
    workingDir = std::string(_workingDir);
    sendEventsToBugsnag = _sendEventsToBugsnag;
    cacheEvents = _cacheEvents && !workingDir.empty();
    cacheFileCharLimit = _cacheFileCharLimit;

    if (!workingDir.empty()) {
        if (workingDir.at(0) != '/') {
            workingDir = "/" + workingDir;
        }
        if (workingDir.back() != '/') {
            workingDir += "/";
        }
    }

    bugsnag_add_on_error(&onError);
}