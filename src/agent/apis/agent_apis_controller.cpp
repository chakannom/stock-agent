#include <core/header/header.hpp>
#include <core/util/response_util.hpp>
#include "agent_apis_controller.hpp"
#include "resource/stock_resource_v1.hpp"
#include "resource/version_resource_v1.hpp"

using namespace web;
using namespace http;
using namespace cks;

AgentApisController::AgentApisController() : BasicController() {
    resources.insert(std::pair<std::wstring, Resource*>(StockResourceV1::KEY, new StockResourceV1()));
    resources.insert(std::pair<std::wstring, Resource*>(VersionResourceV1::KEY, new VersionResourceV1()));
}

AgentApisController::~AgentApisController() {

}

void AgentApisController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&AgentApisController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&AgentApisController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&AgentApisController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&AgentApisController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&AgentApisController::handlePatch, this, std::placeholders::_1));
}

void AgentApisController::handleGet(http_request request) {
    auto path = requestPath(request);

    if (!path.empty() && path.size() > 1 && resources[path[0] + L"_" + path[1]]) {
        resources[path[0] + L"_" + path[1]]->handleGet(path, request);
    }
    else {
        request.reply(status_codes::NotFound);
    }
}

void AgentApisController::handlePatch(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::PATCH));
}

void AgentApisController::handlePut(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::PUT));
}

void AgentApisController::handlePost(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::POST));
}

void AgentApisController::handleDelete(http_request request) {    
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::DEL));
}

void AgentApisController::handleHead(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::HEAD));
}

void AgentApisController::handleOptions(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::OPTIONS));
}

void AgentApisController::handleTrace(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::TRCE));
}

void AgentApisController::handleConnect(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::CONNECT));
}

void AgentApisController::handleMerge(http_request request) {
    request.reply(status_codes::NotImplemented, ResponseUtil::responseNotImpl(methods::MERGE));
}