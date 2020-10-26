#include <WinSock2.h>

#include <core/config/interrupt/interrupt_handler.hpp>
#include <core/util/runtime_util.hpp>

#include <initializer.hpp>

#include <core/config/thirdparty/cpprest/ws_listener.h>

using namespace cfx;
using namespace cks;

int main(int argc, wchar_t* argv[]) {
    /*
    InterruptHandler::hookSIGINT();

    web::websockets::experimental::listener::websocket_listener test;

    test = web::websockets::experimental::listener::websocket_listener(web::uri(L"ws://127.0.0.1:18080"));

    try {
        test.open();
        InterruptHandler::waitForUserInterrupt();
        test.close();
    }
    catch (std::exception& e) {
        std::wcerr << L"somehitng wrong happen! :(" << std::endl;
    }
    catch (...) {
        RuntimeUtil::printStackTrace();
    }
    */

    InterruptHandler::hookSIGINT();

    try {
        Initializer::getInstance()->waitAccept();

        InterruptHandler::waitForUserInterrupt();

        Initializer::getInstance()->waitShutdown();

        Initializer::destroyInstance();
    } catch (std::exception& e) {
        std::wcerr << L"somehitng wrong happen! :(" << std::endl;
    } catch (...) {
        RuntimeUtil::printStackTrace();
    }

    return 0;
}