#include <iostream>

#include "core/config/interrupt/interrupt_handler.hpp"
#include "core/util/runtime_util.hpp"

#include "stock/web/rest/sample_resource.hpp"

using namespace web;
using namespace cfx;

int main(int argc, wchar_t *argv[])
{
    InterruptHandler::hookSIGINT();

    MicroserviceController server;
    server.setEndpoint("http://host_auto_ip4:8080/v1/api");
    
    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "Modern C++ Microservice now listening for requests at: " << server.endpoint() << '\n';
        
        InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << "somehitng wrong happen! :(" << std::endl;
    }
    catch(...) {
        RuntimeUtil::printStackTrace();
    }

    return 0;
}