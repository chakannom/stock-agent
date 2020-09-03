#pragma once

class WmcaIntfHelper {
private:
    const wchar_t* pClassName;
    const wchar_t* pWindowName;
    HINSTANCE hInstance;
public:
    WmcaIntfHelper(const wchar_t* pClassName, const wchar_t* pWindowName);
    ~WmcaIntfHelper() = default;
    ATOM registerWndClass(WNDPROC wndClass);
    HWND initInstance();
    int messageLoop();
};

