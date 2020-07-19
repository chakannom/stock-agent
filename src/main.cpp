#include <iostream>

#include <core/config/interrupt/interrupt_handler.hpp>
#include <core/util/runtime_util.hpp>

#include <agent/apis/agent_apis_controller.hpp>

using namespace web;
using namespace cfx;

int main(int argc, wchar_t *argv[])
{
    InterruptHandler::hookSIGINT();

    AgentApisController agentApisController;
    agentApisController.setEndpoint(L"http://host_auto_ip4:28080/agent/apis/");
    
    try {
        // wait for server initialization...
        agentApisController.accept().wait();
        std::wcout << "StockAgent now listening for requests at: " << agentApisController.endpoint() << std::endl;

        InterruptHandler::waitForUserInterrupt();

        agentApisController.shutdown().wait();
    }
    catch(std::exception & e) {
        std::wcerr << "somehitng wrong happen! :(" << std::endl;
    }
    catch(...) {
        RuntimeUtil::printStackTrace();
    }

    return 0;
}