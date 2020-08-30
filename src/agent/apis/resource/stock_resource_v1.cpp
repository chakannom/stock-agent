#include <thread>
#include <chrono>

#include <core/header/header.hpp>

#include <agent/config/thirdparty/nh_namu/wmca_intf.hpp>

#include "stock_resource_v1.hpp"

using namespace web;
using namespace http;

const std::wstring StockResourceV1::KEY = L"stock_v1";

StockResourceV1::StockResourceV1() {
    std::wcout << L"StockResourceV1-START" << std::endl;

    std::wcout << WM_USER + 0x1000 << std::endl;
    std::wcout << WM_DESTROY << std::endl;

    std::wcout << L"StockResourceV1-END" << std::endl;
}

StockResourceV1::~StockResourceV1() {
}

void StockResourceV1::handleGet(std::vector<std::wstring> & path, http_request & request) {

    static std::wstring test = L"";

    HINSTANCE hInstance = GetModuleHandle(NULL);

    // TODO: 여기에 코드를 입력합니다.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT CALLBACK {
        std::cout << "WndProc:" << message << std::endl;
        switch (message) {
        case WM_USER + 0x1000:
            std::wcout << L"WM_USER" << std::endl;
            test += L"WM_USER";
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

    if (!hWnd)
    {
        return;
    }

    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

    SendMessage(hWnd, WM_USER + 0x1000, 0, 0);
    SendMessage(hWnd, WM_USER + 0x1000, 0, 0);

    SendMessage(hWnd, WM_CLOSE, 0, 0);

    std::wcout << L"handleGet" << std::endl;
    ////////
    try {
        auto response = json::value::object();
        response[L"stock"] = json::value::string(test);
        test.clear();
        request.reply(status_codes::OK, response);
    }
    catch (http_exception const& e) {
        std::wcout << e.what() << std::endl;
    }
}

void StockResourceV1::handlePatch(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handlePut(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handlePost(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleDelete(std::vector<std::wstring> & path, http_request & request) {    
}

void StockResourceV1::handleHead(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleOptions(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleTrace(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleConnect(std::vector<std::wstring> & path, http_request & request) {
}

void StockResourceV1::handleMerge(std::vector<std::wstring> & path, http_request & request) {
}

