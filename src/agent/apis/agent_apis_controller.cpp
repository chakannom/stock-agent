#include <core/header/header.hpp>
#include "agent_apis_controller.hpp"

using namespace web;
using namespace http;

void AgentApisController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&AgentApisController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&AgentApisController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&AgentApisController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&AgentApisController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&AgentApisController::handlePatch, this, std::placeholders::_1));
}

void AgentApisController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == L"version") {
            versionResource.getVersion(message);
        }
    }
    else {
        message.reply(status_codes::NotFound);
    }
}

void AgentApisController::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void AgentApisController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void AgentApisController::handlePost(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void AgentApisController::handleDelete(http_request message) {    
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void AgentApisController::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void AgentApisController::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void AgentApisController::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void AgentApisController::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void AgentApisController::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value AgentApisController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response[L"serviceName"] = json::value::string(L"C++ Mircroservice Sample");
    response[L"http_method"] = json::value::string(method);
    return response ;
}