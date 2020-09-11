# stock-agent

## dependency library
- cpprestsdk (vcpkg)
- boost (vcpkg)
- sqlite3 (vcpkg)
- log4cxx (vcpkg)
- websocketpp (vcpkg)
- cppdb v0.3.1 ( include: core/config/thirdparty/cppdb )
- web::websockets::server ( include: core/config/thirdparty/cpprest )

## how to use log4cxx
LoggerPtr log = Logger::getLogger("NAME");

LOG4CXX_FATAL(log, "fatal output...");
LOG4CXX_ERROR(log, "error output...");
LOG4CXX_WARN(log, "warn output...");
LOG4CXX_INFO(log, "info output...");
LOG4CXX_DEBUG(log, "debug output...");