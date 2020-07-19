#pragma once 

#include <core/controller/basic_controller.hpp>
#include "resource/version_resource.hpp"

using namespace cfx;
using namespace cks;

class AgentApisController : public BasicController, Controller {
private:
    VersionResource versionResource;
    json::value responseNotImpl(const http::method & method);
public:
    AgentApisController() : BasicController() {}
    ~AgentApisController() {}
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