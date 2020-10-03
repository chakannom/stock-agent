#include <iostream>
#include <regex>
#include <core/util/response_util.hpp>

#include "stock_rest_controller.hpp"

StockRestController::StockRestController(const std::wstring& url) : cfx::BasicController() {
    this->setEndpoint(url + L"/apis/stock/v1");
}

void StockRestController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&StockRestController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&StockRestController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&StockRestController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&StockRestController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&StockRestController::handlePatch, this, std::placeholders::_1));
}

void StockRestController::handleGet(http_request request) {
    try {
        auto path = requestPath(request);
        std::wsmatch matches;
        if (std::regex_match(path, matches, std::wregex(L"/connect/status"))) {
            auto response = web::json::value::boolean(stockService.isConnected());
            request.reply(status_codes::OK, response);
        }
        else if (std::regex_match(path, matches, std::wregex(L"/current/items"))) {
            auto response = stockService.getCurrentPriceOfItems();
            request.reply(status_codes::OK, response);
        }
        else if (std::regex_match(path, matches, std::wregex(L"/current/items/(\\d{6})"))) {
            std::wstring code = matches[1];
            auto response = stockService.getCurrentPriceOfItem(code);
            request.reply(status_codes::OK, response);
        }
        else if (std::regex_match(path, matches, std::wregex(L"/test"))) {
            auto response = web::json::value::object();
            response[L"query"] = web::json::value::string(stockService.getTest());
            request.reply(status_codes::OK, response);
        }
    }
    catch (http_exception const& e) {
        request.reply(status_codes::BadRequest, cks::ResponseUtil::responseBadRequest(methods::GET));
    }
    catch (...) {
        request.reply(status_codes::BadRequest, cks::ResponseUtil::responseBadRequest(methods::GET));
    }

    request.reply(status_codes::NotFound, cks::ResponseUtil::responseNotFound(methods::GET));
}

void StockRestController::handlePatch(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::PATCH));
}

void StockRestController::handlePut(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::PUT));
}

void StockRestController::handlePost(http_request request) {;
    try {
        auto path = requestPath(request);
        std::wsmatch matches;
        if (std::regex_match(path, matches, std::wregex(L"/connect"))) {
            auto response = stockService.connect(request.extract_json().get());
            request.reply(status_codes::OK, response);
        }
        else if (std::regex_match(path, matches, std::wregex(L"/disconnect"))) {
            auto response = web::json::value::boolean(stockService.disconnect());
            request.reply(status_codes::OK, response);
        }
    }
    catch (http_exception const& e) {
        request.reply(status_codes::BadRequest, cks::ResponseUtil::responseBadRequest(methods::POST));
    }
    catch (...) {
        request.reply(status_codes::BadRequest, cks::ResponseUtil::responseBadRequest(methods::POST));
    }

    request.reply(status_codes::NotFound, cks::ResponseUtil::responseNotFound(methods::POST));
}

void StockRestController::handleDelete(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::DEL));
}

void StockRestController::handleHead(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::HEAD));
}

void StockRestController::handleOptions(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::OPTIONS));
}

void StockRestController::handleTrace(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::TRCE));
}

void StockRestController::handleConnect(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::CONNECT));
}

void StockRestController::handleMerge(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::MERGE));
}