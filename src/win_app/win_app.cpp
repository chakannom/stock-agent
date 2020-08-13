#include "win_app.hpp"

WinApp::WinApp(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WCHAR * szWindowClassName) {
    this->hInstance = hInstance;
    this->nCmdShow = nCmdShow;
    this->szWindowClassName = szWindowClassName;
}

WinApp::~WinApp() {

}

// 창 클래스를 등록
ATOM WinApp::registerWndClass(WNDPROC wndProc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = wndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClassName;
    wcex.hIconSm        = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

// 인스턴스 핸들을 저장하고 주 창을 만듦
BOOL WinApp::initInstance(WCHAR * szTitle)
{
   HWND hWnd = CreateWindowW(szWindowClassName, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// 메시지 루프
int WinApp::messageLoop() {
    MSG msg;

    // 기본 메시지 루프
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}