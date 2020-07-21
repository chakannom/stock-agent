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
    void handleGet(http_request request) override;
    void handlePut(http_request request) override;
    void handlePost(http_request request) override;
    void handlePatch(http_request request) override;
    void handleDelete(http_request request) override;
    void handleHead(http_request request) override;
    void handleOptions(http_request request) override;
    void handleTrace(http_request request) override;
    void handleConnect(http_request request) override;
    void handleMerge(http_request request) override; 
};