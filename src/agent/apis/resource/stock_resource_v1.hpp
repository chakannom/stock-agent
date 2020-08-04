#pragma once

#include <cpprest/http_msg.h>
#include <core/controller/resource/resource.hpp>

using namespace web;
using namespace http;
using namespace cks;

class StockResourceV1 : public Resource {
public:
    static const std::wstring KEY;
public:
    StockResourceV1();
    ~StockResourceV1();
    void handleGet(std::vector<std::wstring> & path, http_request & request) override;
    void handlePut(std::vector<std::wstring> & path, http_request & request) override;
    void handlePost(std::vector<std::wstring> & path, http_request & request) override;
    void handlePatch(std::vector<std::wstring> & path, http_request & request) override;
    void handleDelete(std::vector<std::wstring> & path, http_request & request) override;
    void handleHead(std::vector<std::wstring> & path, http_request & request) override;
    void handleOptions(std::vector<std::wstring> & path, http_request & request) override;
    void handleTrace(std::vector<std::wstring> & path, http_request & request) override;
    void handleConnect(std::vector<std::wstring> & path, http_request & request) override;
    void handleMerge(std::vector<std::wstring> & path, http_request & request) override;   
};