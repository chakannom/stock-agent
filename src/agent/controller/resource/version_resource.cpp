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
    response[L"status"] = json::value::string(L"ready!");
    message.reply(status_codes::OK, response);
}