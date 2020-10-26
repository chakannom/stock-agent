#pragma once

#include <iostream>
#include <boost/stacktrace.hpp>

namespace cks {
    class RuntimeUtil {
    public:
        static void printStackTrace() {
            std::cout << boost::stacktrace::stacktrace() << std::endl;
        }
    };
}