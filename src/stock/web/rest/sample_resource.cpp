//
//  Created by Ivan Mejia on 12/24/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <core/header/header.hpp>
#include "sample_resource.hpp"

using namespace web;
using namespace http;

void SampleResource::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&SampleResource::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&SampleResource::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&SampleResource::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&SampleResource::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&SampleResource::handlePatch, this, std::placeholders::_1));
}

void SampleResource::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == L"service" && path[1] == L"test") {
            auto response = json::value::object();
            response[L"version"] = json::value::string(L"0.1.1");
            response[L"status"] = json::value::string(L"ready!");
            message.reply(status_codes::OK, response);
        }
    }
    else {
        message.reply(status_codes::NotFound);
    }
}

void SampleResource::handlePatch(http_request message) {

}

void SampleResource::handlePut(http_request message) {

}

void SampleResource::handlePost(http_request message) {

}

void SampleResource::handleDelete(http_request message) {    

}

void SampleResource::handleHead(http_request message) {

}

void SampleResource::handleOptions(http_request message) {

}

void SampleResource::handleTrace(http_request message) {

}

void SampleResource::handleConnect(http_request message) {

}

void SampleResource::handleMerge(http_request message) {

}

json::value SampleResource::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response[L"serviceName"] = json::value::string(L"C++ Mircroservice Sample");
    response[L"http_method"] = json::value::string(method);
    return response ;
}