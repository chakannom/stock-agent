#pragma once

#include <cpprest/http_msg.h>
#include <core/controller/resource/resource.hpp>

using namespace web;
using namespace http;
using namespace cks;

class VersionResource : public Resource {
public:
    VersionResource();
    ~VersionResource();

    void getVersion(http_request message);
};