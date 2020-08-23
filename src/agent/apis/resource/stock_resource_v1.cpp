#include <core/header/header.hpp>

#include <agent/config/global_variable.hpp>
#include <agent/config/thirdparty/nh_namu/wmca_intf.hpp>

#include "stock_resource_v1.hpp"

using namespace web;
using namespace http;

const std::wstring StockResourceV1::KEY = L"stock_v1";

WmcaIntf wmcaIntf;

StockResourceV1::StockResourceV1() {
}

StockResourceV1::~StockResourceV1() {
}

void StockResourceV1::handleGet(std::vector<std::wstring> & path, http_request & request) {
    if (path[2] == L"test") {
        WmcaIntf wmcaIntf;
        GlobalVariable* globalVariable = GlobalVariable::getInstance();
        globalVariable->getHwnd();
    }
}

void StockResourceV1::handlePatch(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handlePut(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handlePost(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleDelete(std::vector<std::wstring> & path, http_request & request) {    
}

void StockResourceV1::handleHead(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleOptions(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleTrace(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleConnect(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleMerge(std::vector<std::wstring> & path, http_request & request) {
}