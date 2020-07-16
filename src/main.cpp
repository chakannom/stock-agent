#include <iostream>

#include "core/config/interrupt/interrupt_handler.hpp"
#include "core/util/runtime_util.hpp"

using namespace cfx;
using namespace cks;

int wmain(int argc, wchar_t *argv[])
{
    InterruptHandler::hookSIGINT();

    try {
        // wait for server initialization...
        InterruptHandler::waitForUserInterrupt();

    }
    catch(std::exception & e) {
        std::wcerr << "somehitng wrong happen! :(" << std::endl;
    }
    catch(...) {
        RuntimeUtil::printStackTrace();
    }

    return 0;
}