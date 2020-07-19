#include <core/header/header.hpp>
#include "agent_controller.hpp"

using namespace web;
using namespace http;

void AgentController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&AgentController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&AgentController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&AgentController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&AgentController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&AgentController::handlePatch, this, std::placeholders::_1));
}

void AgentController::handleGet(http_request message) {
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

void AgentController::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void AgentController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void AgentController::handlePost(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void AgentController::handleDelete(http_request message) {    
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void AgentController::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void AgentController::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void AgentController::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void AgentController::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void AgentController::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value AgentController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response[L"serviceName"] = json::value::string(L"C++ Mircroservice Sample");
    response[L"http_method"] = json::value::string(method);
    return response ;
}