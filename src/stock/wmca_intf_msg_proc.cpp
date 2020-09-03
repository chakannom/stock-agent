#pragma comment(lib, "user32.lib")

#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include <stock/wmca_intf.hpp>

#include "wmca_intf_msg_proc.hpp"

WmcaIntfMsgProc::ResultMsg WmcaIntfMsgProc::connectMsg;
WmcaIntfMsgEvent WmcaIntfMsgProc::connectMsgEvent(&WmcaIntfMsgProc::connectMsg.msg);
WNDPROC WmcaIntfMsgProc::connectWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
    switch (message) {
        case CA_WMCAEVENT:
        {
            switch (wParam) {
                case CA_CONNECTED:          //로그인 성공
                {
                    std::wcout << L"CA_CONNECTED" << std::endl;
                    connectMsgEvent.OnWmConnected((LOGINBLOCK*)lParam);
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                }
                case CA_DISCONNECTED:        //접속 끊김
                {
                    std::wcout << L"CA_DISCONNECTED" << std::endl;
                    connectMsgEvent.OnWmDisconnected();
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                }
                case CA_RECEIVEMESSAGE:     //상태 메시지 수신
                {
                    std::wcout << L"CA_RECEIVEMESSAGE" << std::endl;
                    connectMsgEvent.OnWmReceiveMessage((OUTDATABLOCK*)lParam);
                    break;
                }
                default:
                {
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                }
            }
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
};

std::wstring WmcaIntfMsgProc::sampleData;
WmcaIntfMsgEvent WmcaIntfMsgProc::sampleMsgEvent(&WmcaIntfMsgProc::sampleData);
WNDPROC WmcaIntfMsgProc::sampleWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
    switch (message) {
        case CA_WMCAEVENT:
        {
            switch (wParam) {
                case CA_CONNECTED:          //로그인 성공
                {
                    std::wcout << L"CA_CONNECTED" << std::endl;
                    sampleMsgEvent.OnWmConnected((LOGINBLOCK*)lParam);
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                }
                case CA_DISCONNECTED:        //접속 끊김
                {
                    std::wcout << L"CA_DISCONNECTED" << std::endl;
                    sampleMsgEvent.OnWmDisconnected();
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                }
                case CA_SOCKETERROR:        //통신 오류 발생
                {
                    std::wcout << L"CA_SOCKETERROR" << std::endl;
                    sampleMsgEvent.OnWmSocketError((int)lParam);
                    break;
                }
                case CA_RECEIVEDATA:        //서비스 응답 수신(TR)
                {
                    std::wcout << L"CA_RECEIVEDATA" << std::endl;
                    sampleMsgEvent.OnWmReceiveData((OUTDATABLOCK*)lParam);
                    break;
                }
                case CA_RECEIVESISE:        //실시간 데이터 수신(BC)
                {
                    std::wcout << L"CA_RECEIVESISE" << std::endl;
                    sampleMsgEvent.OnWmReceiveSise((OUTDATABLOCK*)lParam);
                    break;
                }
                case CA_RECEIVEMESSAGE:     //상태 메시지 수신 (입력값이 잘못되었을 경우 문자열형태로 설명이 수신됨)
                {
                    std::wcout << L"CA_RECEIVEMESSAGE" << std::endl;
                    sampleMsgEvent.OnWmReceiveMessage((OUTDATABLOCK*)lParam);
                    break;
                }
                case CA_RECEIVECOMPLETE:    //서비스 처리 완료
                {
                    std::wcout << L"CA_RECEIVECOMPLETE" << std::endl;
                    sampleMsgEvent.OnWmReceiveComplete((OUTDATABLOCK*)lParam);
                    break;
                }
                case CA_RECEIVEERROR:       //서비스 처리중 오류 발생 (입력값 오류등)
                {
                    std::wcout << L"CA_RECEIVEERROR" << std::endl;
                    sampleMsgEvent.OnWmReceiveError((OUTDATABLOCK*)lParam);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
};
