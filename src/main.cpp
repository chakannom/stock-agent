#pragma comment (lib, "user32.lib")

#include <iostream>
#define WIN32_LEAN_AND_MEAN  // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <windows.h>

#include <core/config/interrupt/interrupt_handler.hpp>
#include <core/util/runtime_util.hpp>
#include <agent/apis/agent_apis_controller.hpp>

#define IDC_START_BTN 101
#define IDC_STOP_BTN  102

using namespace web;
using namespace cfx;
using namespace cks;

HINSTANCE hInst;                                // ���� �ν��Ͻ�
WCHAR *szTitle = L"TITLE";                      // ���� ǥ���� �ؽ�Ʈ
WCHAR *szWindowClass = L"CLASSNAME";            // �⺻ â Ŭ���� �̸�
AgentApisController agentApisController;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ ����
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    MSG msg;

    // �⺻ �޽��� ����
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

// â Ŭ������ ���
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

// �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// �� â�� �޽����� ó��
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
                        agentApisController.setEndpoint(L"http://host_auto_ip4:28080/agent/apis");
                        agentApisController.accept().wait();
                        std::wcout << L"StockAgent now listening for requests at: " << agentApisController.endpoint() << std::endl;
                        break;
                    case IDC_STOP_BTN:
                        std::cout << "STOP" << std::endl;
                        agentApisController.shutdown().wait();
                        break;
                }
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}