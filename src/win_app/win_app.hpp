#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

class WinApp {
private:
    HINSTANCE hInstance;
    int  nCmdShow;
    WCHAR * szWindowClassName;
public:
    WinApp(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WCHAR * szWindowClassName);
    ~WinApp(); 
    ATOM registerWndClass(WNDPROC wndProc);
    BOOL initInstance(WCHAR * szTitle);
    int messageLoop();
};