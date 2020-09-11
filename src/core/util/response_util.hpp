#pragma once

#include <cpprest/json.h>
#include <cpprest/http_msg.h>

using namespace web;

namespace cks {
    class ResponseUtil {
    public:
        static json::value responseNotImpl(const http::method & method) {
            auto response = json::value::object();
            response[L"message"] = json::value::string(L"Not Implemented");
            response[L"httpMethod"] = json::value::string(method);
            return response;
        };
        static json::value responseBadRequest(const http::method & method) {
            auto response = json::value::object();
            response[L"message"] = json::value::string(L"Bad Request");
            response[L"httpMethod"] = json::value::string(method);
            return response;
        };
        static json::value responseNotFound(const http::method & method) {
            auto response = json::value::object();
            response[L"message"] = json::value::string(L"Not Found");
            response[L"httpMethod"] = json::value::string(method);
            return response;
        };
    };
}