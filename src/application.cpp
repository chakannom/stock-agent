#include <core/config/interrupt/interrupt_handler.hpp>
#include <core/util/runtime_util.hpp>

#include <initializer.hpp>

using namespace cfx;
using namespace cks;

int main(int argc, wchar_t* argv[]) {

    InterruptHandler::hookSIGINT();

    try {
        Initializer::getInstance()->waitAccept();

        InterruptHandler::waitForUserInterrupt();

        Initializer::getInstance()->waitShutdown();
    } catch (std::exception& e) {
        std::wcerr << L"somehitng wrong happen! :(" << std::endl;
    } catch (...) {
        RuntimeUtil::printStackTrace();
    }

    return 0;
}