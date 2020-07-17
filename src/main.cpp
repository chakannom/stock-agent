#include <iostream>

#include <core/config/interrupt/interrupt_handler.hpp>
#include <core/util/runtime_util.hpp>

#include <stock/web/rest/sample_resource.hpp>

using namespace web;
using namespace cfx;

int main(int argc, wchar_t *argv[])
{
    InterruptHandler::hookSIGINT();

    SampleResource resource;
    resource.setEndpoint(L"http://host_auto_ip4:8080/v1/api");
    
    try {
        // wait for server initialization...
        resource.accept().wait();
        std::wcout << "Modern C++ Microservice now listening for requests at: " << resource.endpoint() << '\n';

        InterruptHandler::waitForUserInterrupt();

        resource.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << "somehitng wrong happen! :(" << std::endl;
    }
    catch(...) {
        RuntimeUtil::printStackTrace();
    }

    return 0;
}