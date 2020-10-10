#include "stock_executor_process.hpp"

StockExecutorProcess::StockExecutorProcess() : si({ 0, }), pi({ 0, }) {
    start();
}

StockExecutorProcess::~StockExecutorProcess() {
    stop();
}

void StockExecutorProcess::start() {
    if (running()) kill();

    LPWSTR applicationName = (LPWSTR)L"C:\\Users\\chakannom\\Development\\workspace\\visualstudio\\stock\\executor\\stock-executor-for-ebest.exe";
    LPWSTR commandLine = (LPWSTR)L"stock-executor-for-ebest.exe --execute uuid";
    si.cb = sizeof(si);
    CreateProcess(applicationName, commandLine, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
}

void StockExecutorProcess::stop() {
    TerminateProcess(pi.hProcess, 0);
    WaitForSingleObject(pi.hProcess, 5000);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

bool StockExecutorProcess::running() {
    HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR-FOR-EBEST");
    if (hWnd == NULL) {
        return false;
    }
    return true;
}

void StockExecutorProcess::kill() {
    HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR-FOR-EBEST");
    if (!hWnd) return;
    DWORD processId;
    GetWindowThreadProcessId(hWnd, &processId);
    if (!processId) return;
    HANDLE hProcess = OpenProcess(MAXIMUM_ALLOWED, TRUE, processId);
    TerminateProcess(hProcess, 0);
    WaitForSingleObject(hProcess, 5000);
    CloseHandle(hProcess);
}

