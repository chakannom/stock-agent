#pragma once

const DWORD WM_STOCK_EXECUTOR_SETSTRINGVARIABLE = WM_USER + 1001;
const DWORD WM_STOCK_AGENT_SETSTRINGVARIABLE = WM_USER + 2001;

const DWORD IDC_BTN_LOGIN = 1000;
const DWORD IDC_BTN_LOGOUT = 1001;
const DWORD IDC_BTN_ISLOGIN = 1002;
const DWORD IDC_BTN_STOCKSBYGUBUN = 1003;
const DWORD IDC_BTN_STOCKCURRENTASKINGPRICE = 1004;
const DWORD IDC_BTN_STOCKCURRENTMARKETPRICE = 1005;

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

