#pragma once

#include <cpprest/json.h>

#include <stock/wmca_intf.hpp>

class StockService {
private:
    WmcaIntf wmcaIntf;
    std::mutex stockMutex;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
public:
    StockService();
    ~StockService();
    std::wstring connect(const web::json::value & json);
    void disconnect();
    bool isConnected();
    void getBalance(); // 잔고조회

    std::wstring getTest();
};

