#pragma comment(lib, "user32.lib")

#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include "stock_service_helper.hpp"

std::wstring StockServiceHelper::data;
WNDPROC StockServiceHelper::wndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
    switch (message) {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
};

StockServiceHelper::StockServiceHelper() {
    this->data.clear();
    this->pClassName = L"STOCK_AGENT-STOCK_SERVICE_HELPER";
    this->pWindowName = L"STOCK_AGENT-STOCK_SERVICE_HELPER";
    this->hInstance = GetModuleHandleW(nullptr);
    registerWndClass();
    initInstance();
}

ATOM StockServiceHelper::registerWndClass() {
    WNDCLASSEXW wcex = { 0, };

    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = pClassName;

    return RegisterClassExW(&wcex);
}

HWND StockServiceHelper::initInstance() {
    HWND hWnd = CreateWindowW(pClassName, pWindowName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd) {
        return nullptr;
    }

    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

    return hWnd;
}

int StockServiceHelper::messageLoop() {
    MSG msg = { 0 };

    while (GetMessageW(&msg, NULL, 0, 0)) {
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}

std::wstring StockServiceHelper::getData() {
    return data;
}