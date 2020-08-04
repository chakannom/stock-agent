#include <core/header/header.hpp>
#include "version_resource_v1.hpp"

using namespace web;
using namespace http;

const std::wstring VersionResourceV1::KEY = L"version_v1";

VersionResourceV1::VersionResourceV1() {
}

VersionResourceV1::~VersionResourceV1() {
}

void VersionResourceV1::handleGet(std::vector<std::wstring> & path, http_request & request) {
    try {
        auto response = json::value::object();
        response[L"version"] = json::value::string(L"0.0.1");
        response[L"date"] = json::value::string(L"##DATE##");
        // "Copyright 2020 ChaKanS. All rights reserved."
        request.reply(status_codes::OK, response);
    } catch (http_exception const & e) {
        std::wcout << e.what() << std::endl;
    }
}

void VersionResourceV1::handlePatch(std::vector<std::wstring> & path, http_request & request) {
}

void VersionResourceV1::handlePut(std::vector<std::wstring> & path, http_request & request) {
}

void VersionResourceV1::handlePost(std::vector<std::wstring> & path, http_request & request) {
}

void VersionResourceV1::handleDelete(std::vector<std::wstring> & path, http_request & request) {    
}

void VersionResourceV1::handleHead(std::vector<std::wstring> & path, http_request & request) {
}

void VersionResourceV1::handleOptions(std::vector<std::wstring> & path, http_request & request) {
}

void VersionResourceV1::handleTrace(std::vector<std::wstring> & path, http_request & request) {
}

void VersionResourceV1::handleConnect(std::vector<std::wstring> & path, http_request & request) {
}

void VersionResourceV1::handleMerge(std::vector<std::wstring> & path, http_request & request) {
}