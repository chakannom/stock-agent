#pragma once

#include <stock/wmca_intf.hpp>

class StockService {
private:
    WmcaIntf wmcaIntf;
public:
    StockService() = default;
    ~StockService() = default;
    std::wstring connect();
    void disconnect();
    void getBalance(); // 잔고조회

    std::wstring getTest();
};

