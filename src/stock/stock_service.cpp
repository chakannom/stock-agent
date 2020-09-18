#define UNICODE
#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include <core/util/string_util.hpp>

#include "stock_service.hpp"
#include "stock_service_helper.hpp"

StockService::StockService() : si({ 0, }), pi({ 0, }) {
    //LPWSTR command = (LPWSTR)L"C:\\Users\\chakannom\\Development\\workspace\\visualstudio\\namu\\Debug\\WMCALOADER.test";
    //si.cb = sizeof(si);
    //CreateProcess(command, NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
}

StockService::~StockService() {
}

std::wstring StockService::connect(const web::json::value& cRequestJson) {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    StockServiceHelper stockServiceHelper;

    HWND hWnd = FindWindow(0, L"STOCK-EXECUTOR");

    //{
    //    "id" : "username",
    //    "pw" : "password",
    //    "certPw" : "certificate password"
    //}

    std::wstring jsonString = cRequestJson.serialize();

    COPYDATASTRUCT cds;
    cds.dwData = WM_USER + 1001;
    cds.cbData = jsonString.size() * sizeof(wchar_t);
    cds.lpData = (PVOID)jsonString.c_str();

    SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&cds);
    SendMessage(hWnd, WM_COMMAND, 1000, 0);

    stockServiceHelper.messageLoop();

    return stockServiceHelper.getData();
}

std::wstring StockService::disconnect() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    StockServiceHelper stockServiceHelper;

    HWND hWnd = FindWindow(0, L"STOCK-EXECUTOR");

    SendMessage(hWnd, WM_COMMAND, 1001, 0);

    stockServiceHelper.messageLoop();

    return stockServiceHelper.getData();
    //if (isConnected()) {
        //wmcaIntf.Disconnect();
    //}
}

bool StockService::isConnected() {
    //return wmcaIntf.IsConnected();
    return false;
}

void StockService::getBalance() {

}

std::wstring StockService::getTest() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    /*
    WmcaIntfMsgProc::sampleData.clear();

    WmcaIntfHelper wmcaIntfHelper(L"GetTest", L"GetTest");
    wmcaIntfHelper.registerWndClass(WmcaIntfMsgProc::sampleWndProc);
    wmcaIntfHelper.initInstance();

    HWND hWnd = FindWindow(0, L"OpenAPI_Test");
    SendMessage(hWnd, WM_COMMAND, 1003, 0);

    wmcaIntfHelper.messageLoop();

    std::wstring str(WmcaIntfMsgProc::sampleData);
    WmcaIntfMsgProc::sampleData.clear();
    return str;
    */
    return std::wstring(L"getTest");
}
