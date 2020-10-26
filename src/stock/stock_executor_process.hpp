#pragma once
#include <windows.h>

class StockExecutorProcess
{
private:
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
public:
    StockExecutorProcess();
    ~StockExecutorProcess();
private:
    void start();
    void stop();
    bool running();
    void kill();
};

