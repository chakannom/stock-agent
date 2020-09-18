#pragma once

#include <windows.h>
#include <cpprest/json.h>

class StockService {
private:
    std::mutex stockMutex;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
public:
    StockService();
    ~StockService();
    std::wstring connect(const web::json::value & json);
    std::wstring disconnect();
    bool isConnected();
    void getBalance(); // 잔고조회

    std::wstring getTest();
};

