#pragma once

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

class StockResourceV1 {
public:
    static const std::wstring KEY;
public:
    StockResourceV1();
    ~StockResourceV1();
    void handleGet(std::vector<std::wstring> & path, http_request & request);
    void handlePut(std::vector<std::wstring> & path, http_request & request);
    void handlePost(std::vector<std::wstring> & path, http_request & request);
    void handlePatch(std::vector<std::wstring> & path, http_request & request);
    void handleDelete(std::vector<std::wstring> & path, http_request & request);
    void handleHead(std::vector<std::wstring> & path, http_request & request);
    void handleOptions(std::vector<std::wstring> & path, http_request & request);
    void handleTrace(std::vector<std::wstring> & path, http_request & request);
    void handleConnect(std::vector<std::wstring> & path, http_request & request);
    void handleMerge(std::vector<std::wstring> & path, http_request & request);   
};