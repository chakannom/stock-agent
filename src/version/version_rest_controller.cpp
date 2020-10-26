#include <core/util/response_util.hpp>

#include "version_rest_controller.hpp"

VersionRestController::VersionRestController(const std::wstring& url) : cfx::BasicController() {
    this->setEndpoint(url + L"/apis/version/v1");
}

void VersionRestController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&VersionRestController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&VersionRestController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&VersionRestController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&VersionRestController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&VersionRestController::handlePatch, this, std::placeholders::_1));
}

void VersionRestController::handleGet(http_request request) {
    try {
        auto response = json::value::object();
        response[L"version"] = json::value::string(L"0.0.1");
        response[L"date"] = json::value::string(L"##DATE##");
        // "Copyright 2020 ChaKanS. All rights reserved."
        request.reply(status_codes::OK, response);
    }
    catch (http_exception const & e) {
        std::wcout << e.what() << std::endl;
    }
}

void VersionRestController::handlePatch(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::PATCH));
}

void VersionRestController::handlePut(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::PUT));
}

void VersionRestController::handlePost(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::POST));
}

void VersionRestController::handleDelete(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::DEL));
}

void VersionRestController::handleHead(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::HEAD));
}

void VersionRestController::handleOptions(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::OPTIONS));
}

void VersionRestController::handleTrace(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::TRCE));
}

void VersionRestController::handleConnect(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::CONNECT));
}

void VersionRestController::handleMerge(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::MERGE));
}