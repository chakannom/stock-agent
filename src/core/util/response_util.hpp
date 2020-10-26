#pragma once

#include <cpprest/json.h>
#include <cpprest/http_msg.h>

namespace cks {
    class ResponseUtil {
    public:
        static web::json::value responseNotImpl(const web::http::method & method) {
            auto response = web::json::value::object();
            response[L"message"] = web::json::value::string(L"Not Implemented");
            response[L"httpMethod"] = web::json::value::string(method);
            return response;
        };
        static web::json::value responseBadRequest(const web::http::method & method) {
            auto response = web::json::value::object();
            response[L"message"] = web::json::value::string(L"Bad Request");
            response[L"httpMethod"] = web::json::value::string(method);
            return response;
        };
        static web::json::value responseNotFound(const web::http::method & method) {
            auto response = web::json::value::object();
            response[L"message"] = web::json::value::string(L"Not Found");
            response[L"httpMethod"] = web::json::value::string(method);
            return response;
        };
    };
}