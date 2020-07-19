#pragma once

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

class VersionResource {
public:
    VersionResource();
    ~VersionResource();

    void getVersion(http_request message);
};