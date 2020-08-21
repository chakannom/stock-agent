#pragma comment (lib, "user32.lib")

#include <iostream>
#include <win_app/win_app.hpp>

#include <core/config/interrupt/interrupt_handler.hpp>
#include <core/util/runtime_util.hpp>
#include <agent/apis/agent_apis_controller.hpp>
#include <agent/config/thirdparty/nh_namu/wmca_intf.hpp>

#define IDC_START_BTN 101
#define IDC_STOP_BTN  102
#define MAX_LOADSTRING 100

using namespace web;
using namespace cfx;
using namespace cks;

HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING] = L"TEST";                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING] = L"TEST";           // 기본 창 클래스 이름
AgentApisController agentApisController;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	WinApp winApp(hInstance, hPrevInstance, lpCmdLine, nCmdShow, szWindowClass);

	winApp.registerWndClass(WndProc);

	// 애플리케이션 초기화 수행
	if (!winApp.initInstance(szTitle)) {
        return FALSE;
    }

	return winApp.messageLoop();
}

// 주 창의 메시지 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            {
                SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDC_START_BTN, BN_CLICKED), (LPARAM)0);
                SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDC_STOP_BTN, BN_CLICKED), (LPARAM)0);
            }
            break;
        case WM_COMMAND:
            {
                switch (LOWORD(wParam)) {
                    case IDC_START_BTN:
                        std::cout << "START" << std::endl;
                        // agentApisController.setEndpoint(L"http://host_auto_ip4:28080/agent/apis");
                        // agentApisController.accept().wait();
                        // std::wcout << L"StockAgent now listening for requests at: " << agentApisController.endpoint() << std::endl;
                        break;
                    case IDC_STOP_BTN:
                        std::cout << "STOP" << std::endl;
                        // agentApisController.shutdown().wait();
                        break;
                }
            }
            break;
        case CA_WMCAEVENT:
            std::cout << "CA_WMCAEVENT" << std::endl;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}