#include <core/header/header.hpp>
#include "version_resource.hpp"

using namespace web;
using namespace http;

VersionResource::VersionResource() {

}

VersionResource::~VersionResource() {

}

void VersionResource::getVersion(http_request message) {
    auto response = json::value::object();
    response[L"version"] = json::value::string(L"0.0.1");
    response[L"date"] = json::value::string(L"##DATE##");
    // "Copyright 2020 ChaKanS. All rights reserved."
    message.reply(status_codes::OK, response);
}