#pragma once

class StockServiceHelper {
private:
    static std::wstring data;
    static WNDPROC wndProc;
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

