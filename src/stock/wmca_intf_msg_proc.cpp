#pragma comment(lib, "user32.lib")

#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include <stock/wmca_intf.hpp>

#include "wmca_intf_msg_proc.hpp"

WmcaIntfMsgProc::ResultMsg WmcaIntfMsgProc::connectMsg;
WNDPROC WmcaIntfMsgProc::connectWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
    switch (message) {
        case CA_WMCAEVENT:
        {
            switch (wParam) {
                case CA_CONNECTED:          //로그인 성공
                {
                    std::wcout << L"CA_CONNECTED" << std::endl;
                    LOGINBLOCK* pLogin = (LOGINBLOCK*)lParam;
                    //접속시각 출력
                    char szText[256] = { 0 };
                    strncpy(szText, pLogin->pLoginInfo->szDate, sizeof pLogin->pLoginInfo->szDate);
                    std::string strText(szText);
                    connectMsg.msg += L"접속시각 : " + std::wstring(strText.begin(), strText.end()) + L" || ";
                    
                    //계좌번호 출력
                    char szAccountCount[8] = { 0 };
                    strncpy(szAccountCount, pLogin->pLoginInfo->szAccountCount, sizeof pLogin->pLoginInfo->szAccountCount);
                    int	nAccountCount = atoi(szAccountCount);

                    connectMsg.msg += L"계좌번호: [ ";

                    for (int i = 0; i < nAccountCount; i++) {
                        char szAccountNo[16] = { 0 };
                        strncpy(szAccountNo, (char*)&pLogin->pLoginInfo->accountlist[i].szAccountNo, sizeof pLogin->pLoginInfo->accountlist[i].szAccountNo);

                        std::string strAccountNo(szAccountNo);
                        connectMsg.msg += std::wstring(strAccountNo.begin(), strAccountNo.end()) + L',';
                    }

                    connectMsg.msg += L" ] || ";

                    connectMsg.msg += L"정상 접속되었습니다 || ";
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                }
                case CA_RECEIVEMESSAGE:     //상태 메시지 수신
                {
                    std::wcout << L"CA_RECEIVEMESSAGE" << std::endl;
                    OUTDATABLOCK* pMessage = (OUTDATABLOCK*)lParam;
                    MSGHEADER* pMsgHeader = (MSGHEADER*)pMessage->pData->szData;
                    std::wstring wstrTrIndex(std::to_wstring(pMessage->TrIndex));
                    // pMsgHeader->msg_cd
                    std::wstring wstrMsgCd;
                    int lenStrMsgCd = -1;
                    int nCharsStrMsgCd = MultiByteToWideChar(CP_ACP, 0, pMsgHeader->msg_cd, lenStrMsgCd, NULL, 0);
                    wstrMsgCd.resize(nCharsStrMsgCd);
                    MultiByteToWideChar(CP_ACP, 0, pMsgHeader->msg_cd, lenStrMsgCd, const_cast<wchar_t*>(wstrMsgCd.c_str()), nCharsStrMsgCd);
                    // pMsgHeader->user_msg
                    std::wstring wstrUserMsg;
                    int lenStrUserMsg = -1;
                    int nCharsStrUserMsg = MultiByteToWideChar(CP_ACP, 0, pMsgHeader->user_msg, lenStrUserMsg, NULL, 0);
                    wstrMsgCd.resize(nCharsStrUserMsg);
                    MultiByteToWideChar(CP_ACP, 0, pMsgHeader->user_msg, lenStrUserMsg, const_cast<wchar_t*>(wstrMsgCd.c_str()), nCharsStrUserMsg);

                    connectMsg.msg += L"[" + wstrTrIndex + L"] " + wstrMsgCd + L" : " + wstrUserMsg + L" || ";
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

std::wstring WmcaIntfMsgProc::sampleData = L"";
WNDPROC WmcaIntfMsgProc::sampleWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
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
                    LOGINBLOCK* pLogin = (LOGINBLOCK*)lParam;
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
