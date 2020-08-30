#pragma once
#pragma comment (lib, "log4cxx.lib")
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

namespace cks {
    class LoggerHandler {
    public:
        static void initialize(const wchar_t* conf_path) {
            PropertyConfigurator::configure(File(conf_path));
        }
    };
}