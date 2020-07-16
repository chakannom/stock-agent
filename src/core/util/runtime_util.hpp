#pragma once

// #include <execinfo.h>
// #include <unistd.h>

namespace cks {
    class RuntimeUtil {
    public:
        static void printStackTrace() {
            const int MAX_CALLSTACK = 100;
            void * callstack[MAX_CALLSTACK];
            int frames;

            // 윈도우에 맞게 변경해야 함
                        
            // // get void*'s for all entries on the stack...
            // frames = backtrace(callstack, MAX_CALLSTACK);

            // // print out all the frames to stderr...
            // backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
        }
    };
}