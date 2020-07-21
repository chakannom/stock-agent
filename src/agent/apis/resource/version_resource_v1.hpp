#pragma once

#include <cpprest/http_msg.h>
#include <core/controller/resource/resource.hpp>

using namespace web;
using namespace http;
using namespace cks;

class VersionResourceV1 : public Resource {
public:
    VersionResourceV1();
    ~VersionResourceV1();
    void handleGet(std::vector<std::wstring> & path, http_request & message) override;
    void handlePut(std::vector<std::wstring> & path, http_request & message) override;
    void handlePost(std::vector<std::wstring> & path, http_request & message) override;
    void handlePatch(std::vector<std::wstring> & path, http_request & message) override;
    void handleDelete(std::vector<std::wstring> & path, http_request & message) override;
    void handleHead(std::vector<std::wstring> & path, http_request & message) override;
    void handleOptions(std::vector<std::wstring> & path, http_request & message) override;
    void handleTrace(std::vector<std::wstring> & path, http_request & message) override;
    void handleConnect(std::vector<std::wstring> & path, http_request & message) override;
    void handleMerge(std::vector<std::wstring> & path, http_request & message) override;   
};