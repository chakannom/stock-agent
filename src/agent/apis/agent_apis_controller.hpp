#pragma once 

#include <map>
#include <core/controller/basic_controller.hpp>
#include <core/controller/resource/resource.hpp>

using namespace cfx;
using namespace cks;

class AgentApisController : public BasicController, Controller {
private:
    std::map<std::wstring, Resource*> resources;
public:
    AgentApisController();
    ~AgentApisController();
private:
    void initRestOpHandlers() override; 
    void handleGet(http_request message) override;
    void handlePut(http_request message) override;
    void handlePost(http_request message) override;
    void handlePatch(http_request message) override;
    void handleDelete(http_request message) override;
    void handleHead(http_request message) override;
    void handleOptions(http_request message) override;
    void handleTrace(http_request message) override;
    void handleConnect(http_request message) override;
    void handleMerge(http_request message) override; 
};