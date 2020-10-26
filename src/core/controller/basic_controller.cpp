//
//  Created by Ivan Mejia on 12/03/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs. All rights reserved.
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

#include <core/util/network_util.hpp>
#include "basic_controller.hpp"

namespace cfx {
    void BasicController::setEndpoint(const std::wstring& value) {
        uri endpointURI(value);
        uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == L"host_auto_ip4") {
            endpointBuilder.set_host(NetworkUtil::hostIP4());
        }
        else if (endpointURI.host() == L"host_auto_ip6") {
            endpointBuilder.set_host(NetworkUtil::hostIP6());
        }
        else {
            endpointBuilder.set_host(endpointURI.host());
        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        _listener = http_listener(endpointBuilder.to_uri());
    }

    utility::string_t BasicController::endpoint() const {
        return _listener.uri().to_string();
    }

    pplx::task<void> BasicController::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> BasicController::shutdown() {
        return _listener.close();
    }

    utility::string_t BasicController::requestPath(const http_request& request) {
        return uri::decode(request.relative_uri().path());   
    }

    std::vector<utility::string_t> BasicController::splittedRequestPath(const http_request& request) {
        auto relativePath = requestPath(request);
        return uri::split_path(relativePath);
    }

    utility::string_t BasicController::requestQuery(const http_request& request) {
        return request.relative_uri().query();
    }

    std::map<utility::string_t, utility::string_t> BasicController::splittedRequestQuery(const http_request& request) {
        auto relativeQuery = requestQuery(request);
        return uri::split_query(relativeQuery);
    }
}