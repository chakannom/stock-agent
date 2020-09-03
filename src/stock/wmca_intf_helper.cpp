#pragma comment(lib, "user32.lib")

#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include "wmca_intf_helper.hpp"

WmcaIntfHelper::WmcaIntfHelper(const wchar_t* pClassName, const wchar_t* pWindowName) {
    this->pClassName = pClassName;
    this->pWindowName = pWindowName;
    this->hInstance = GetModuleHandleW(nullptr);
}

ATOM WmcaIntfHelper::registerWndClass(WNDPROC wndClass) {
    WNDCLASSEXW wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndClass;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = pClassName;

    return RegisterClassExW(&wcex);
}

HWND WmcaIntfHelper::initInstance() {
    HWND hWnd = CreateWindowW(pClassName, pWindowName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd) {
        return nullptr;
    }

    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

    return hWnd;
}

int WmcaIntfHelper::messageLoop() {
    MSG msg = { 0 };

    while (GetMessageW(&msg, NULL, 0, 0)) {
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}