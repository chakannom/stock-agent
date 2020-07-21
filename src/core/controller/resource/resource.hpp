#pragma once

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

namespace cks {
    class Resource {
    public:
        static const std::wstring KEY;
    public:
        virtual void handleGet(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handlePut(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handlePost(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handleDelete(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handlePatch(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handleHead(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handleOptions(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handleTrace(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handleConnect(std::vector<std::wstring> & path, http_request & request) = 0;
        virtual void handleMerge(std::vector<std::wstring> & path, http_request & request) = 0;
    };
}