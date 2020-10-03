#pragma once

#include <cpprest/json.h>
#include <stock/stock_executor_process.hpp>
#include <stock/stock_repository.hpp>

class StockService {
private:
    std::mutex stockMutex;
    StockExecutorProcess stockExecutorProcess;
    StockRepository stockRepository;
    long delayMilliseconds;
public:
    StockService();
    ~StockService() = default;
    std::wstring connect(const web::json::value& reqJson);
    std::wstring disconnect();
    bool isConnected();
    std::wstring getCurrentPriceOfItems();
    std::wstring getCurrentPriceOfItem(std::wstring& code);
    void getBalance(); // 잔고조회
private:
    web::json::value getResponseJson(const wchar_t* pRequestMessage, DWORD btnId);

public:
    std::wstring getTest();
};

