#pragma comment(lib, "user32.lib")

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

#include "wmca_intf_helper.hpp"

WNDPROC WmcaIntfHelper::sampleWndProc = nullptr;
std::wstring WmcaIntfHelper::sampleData = L"";

WmcaIntfHelper::WmcaIntfHelper(const wchar_t* pClassName, const wchar_t* pWindowName) {
    this->pClassName = pClassName;
    this->pWindowName = pWindowName;
    this->hInstance = GetModuleHandleW(nullptr);
}

ATOM WmcaIntfHelper::RegisterWndClass(WNDPROC wndClass) {
    WNDCLASSEXW wcex = {0};

    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndClass;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = pClassName;

    return RegisterClassExW(&wcex);
}

HWND WmcaIntfHelper::InitInstance() {
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
    MSG msg = {0};

    while (GetMessageW(&msg, NULL, 0, 0)) {
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}

void WmcaIntfHelper::generateWndProcFunctions() {
    sampleWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
        std::wcout << L"WndProcSample : " << message << std::endl;
        switch (message) {
            case WM_USER + 0x1000:
                sampleData += L"WM_USER + 0x1000";
                return 0;
            case CA_WMCAEVENT:
                {
                    switch (wParam) {
                        case CA_CONNECTED:          //로그인 성공
                            {
                                std::wcout << L"CA_CONNECTED" << std::endl;
                                LOGINBLOCK* pLogin = (LOGINBLOCK*) lParam;
                                char szText[256] = { 0 };
                                strncpy(szText, pLogin->pLoginInfo->szDate, sizeof pLogin->pLoginInfo->szDate);
                                std::string strText(szText);
                                sampleData += L"CONNECTED_TIME : " + std::wstring(strText.begin(), strText.end());
                                sampleData += std::wstring(L"안녕");
                                SendMessage(hWnd, WM_CLOSE, 0, 0);
                            }
                            break;
                        case CA_DISCONNECTED:        //접속 끊김
                            std::wcout << L"CA_DISCONNECTED" << std::endl;
                            break;
                        case CA_SOCKETERROR:        //통신 오류 발생
                            std::wcout << L"CA_SOCKETERROR" << std::endl;
                            break;
                        case CA_RECEIVEDATA:        //서비스 응답 수신(TR)
                            std::wcout << L"CA_RECEIVEDATA" << std::endl;
                            break;
                        case CA_RECEIVESISE:        //실시간 데이터 수신(BC)
                            std::wcout << L"CA_RECEIVESISE" << std::endl;
                            break;
                        case CA_RECEIVEMESSAGE:     //상태 메시지 수신 (입력값이 잘못되었을 경우 문자열형태로 설명이 수신됨)
                            std::wcout << L"CA_RECEIVEMESSAGE" << std::endl;
                            break;
                        case CA_RECEIVECOMPLETE:    //서비스 처리 완료
                            std::wcout << L"CA_RECEIVECOMPLETE" << std::endl;
                            break;
                        case CA_RECEIVEERROR:       //서비스 처리중 오류 발생 (입력값 오류등)
                            std::wcout << L"CA_RECEIVEERROR" << std::endl;
                            break;
                        default:
                            break;
                    }
                }
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    };
}