#pragma once

#include <cpprest/json.h>
#include <cpprest/http_msg.h>

using namespace web;

namespace cks {
    class ResponseUtil {
    public:
        static json::value responseNotImpl(const http::method & method) {
            auto response = json::value::object();
            response[L"serviceName"] = json::value::string(L"StockAgent");
            response[L"httpMethod"] = json::value::string(method);
            return response ;
        }
    };
}