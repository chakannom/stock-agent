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
        auto response = json::value::object();
        response[L"test"] = json::value::string(stockService.connect());
        request.reply(status_codes::OK, response);
    }
    catch (http_exception const& e) {
        std::wcout << e.what() << std::endl;
    }
    //request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::GET));
}

void StockRestController::handlePatch(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::PATCH));
}

void StockRestController::handlePut(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::PUT));
}

void StockRestController::handlePost(http_request request) {
    request.reply(status_codes::NotImplemented, cks::ResponseUtil::responseNotImpl(methods::POST));
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