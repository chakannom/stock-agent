#pragma once

const DWORD WM_STOCK_AGENT_SETSTRINGVARIABLE = WM_USER + 2001;

class StockServiceHelper {
private:
    static std::wstring data;
    static WNDPROC wndProc;
    static BOOL OnCopyData(COPYDATASTRUCT* pCopyDataStruct);
    const wchar_t* pClassName;
    const wchar_t* pWindowName;
    HINSTANCE hInstance;
public:
    StockServiceHelper();
    ~StockServiceHelper() = default;
    int messageLoop();
    std::wstring getData();
private:
    ATOM registerWndClass();
    HWND initInstance();
};

