#pragma once

#include <cpprest/json.h>
#include <stock/stock_executor_process.hpp>
#include <stock/stock_repository.hpp>

class StockService {
public:
    StockService();
    ~StockService() = default;
    web::json::value login(const web::json::value& reqJson);
    bool logout();
    bool isLogin();
    web::json::value getStocksByGubun(const std::wstring& gubun);
    web::json::value getStockCurrentAskingPrice(const std::wstring& code);
    web::json::value getStockCurrentMarketPrice(const std::wstring& code);

    void getBalance(); // 잔고조회
private:
    std::mutex stockMutex;
    StockExecutorProcess stockExecutorProcess;
    StockRepository stockRepository;
    std::map<std::wstring, std::wstring> stockGubun;
    long delayMilliseconds;

    web::json::value getResponseJson(const wchar_t* pRequestMessage, DWORD btnId);

public:
    std::wstring getTest();
};

