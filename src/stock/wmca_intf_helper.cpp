#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

#include "wmca_intf_helper.hpp"

std::wstring WmcaIntfHelper::getTest(WmcaIntf & wmcaIntf) {

    static std::wstring test = L"";

    HINSTANCE hInstance = GetModuleHandle(NULL);

    // TODO: 여기에 코드를 입력합니다.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT CALLBACK {
        std::wcout << L"lpfnWndProc : " << message << std::endl;
        switch (message) {
            case WM_USER + 0x1000:
                test += L"WM_USER + 0x1000";
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
                                test += L"접속시각 : " + std::wstring(strText.begin(), strText.end());
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
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = nullptr;
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TEST";
    wcex.hIconSm = nullptr;
    RegisterClassExW(&wcex);

    // 애플리케이션 초기화를 수행합니다:
    HWND hWnd = CreateWindowW(L"TEST", L"TEST", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return L"";
    }

    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

    wmcaIntf.Connect(hWnd, CA_WMCAEVENT, 'T', 'W', "", "", "");

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }

    std::wstring message(test);
    test.clear();
    return message;
}