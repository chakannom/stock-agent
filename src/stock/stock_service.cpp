#define UNICODE
#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include <core/util/string_util.hpp>
#include <stock/stock_service_helper.hpp>

#include "stock_service.hpp"

//------------------------------------------------------------------
/** 
 * RequestJson Format:
 * {
 *      "id" : "username",
 *      "pw" : "password",
 *      "certPw" : "certificate password"
 * }
 */
std::wstring StockService::connect(const web::json::value& reqJson) {
    if (!isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);
        StockServiceHelper stockServiceHelper;

        HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR");

        std::wstring jsonString = reqJson.serialize();

        COPYDATASTRUCT cds;
        cds.dwData = WM_STOCK_EXECUTOR_SETSTRINGVARIABLE;
        cds.cbData = jsonString.size() * sizeof(wchar_t);
        cds.lpData = (PVOID)jsonString.c_str();

        SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&cds);
        SendMessage(hWnd, WM_COMMAND, IDC_BTN_CONNECT, 0);

        stockServiceHelper.messageLoop();

        return stockServiceHelper.getData();
    }
    else {
        // 연결 중 호출한 경우 같은 데이터 전달
    }
}

//------------------------------------------------------------------
std::wstring StockService::disconnect() {
    if (isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);
        StockServiceHelper stockServiceHelper;

        HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR");

        SendMessage(hWnd, WM_COMMAND, IDC_BTN_DISCONNECT, 0);

        stockServiceHelper.messageLoop();

        return stockServiceHelper.getData();
    }
    else {
        // 연결 중이 아닌데 호출한 경우 연결 해제된 상태임을 알려주는 데이터 전달
    }
}

//------------------------------------------------------------------
bool StockService::isConnected() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    StockServiceHelper stockServiceHelper;

    HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR");

    SendMessage(hWnd, WM_COMMAND, IDC_BTN_ISCONNECTED, 0);

    stockServiceHelper.messageLoop();

    std::wstring data = stockServiceHelper.getData();

    web::json::value resJson = web::json::value::parse(data);
    return resJson.at(L"data").at(L"status").as_bool();
}

//------------------------------------------------------------------
/**
 * RequestJson Format:
 * {
 *      "code" : "000000"
 * }
 */
std::wstring StockService::getCurrentPriceOfItem(std::wstring& code) {
    if (isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);
        StockServiceHelper stockServiceHelper;

        HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR");

        std::wstring jsonString = L"{ \"code\": \"" + code + L"\"}";

        COPYDATASTRUCT cds;
        cds.dwData = WM_STOCK_EXECUTOR_SETSTRINGVARIABLE;
        cds.cbData = jsonString.size() * sizeof(wchar_t);
        cds.lpData = (PVOID)jsonString.c_str();

        SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&cds);
        SendMessage(hWnd, WM_COMMAND, IDC_BTN_INQUIRECURRENTPRICE, 0);

        stockServiceHelper.messageLoop();

        return stockServiceHelper.getData();
    }
    else {
        // 연결 중이 아닌데 호출한 경우 연결이 필요하다는 데이터 전달
    }
}

//------------------------------------------------------------------
void StockService::getBalance() {

}

//------------------------------------------------------------------
std::wstring StockService::getTest() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    /*
    WmcaIntfMsgProc::sampleData.clear();

    WmcaIntfHelper wmcaIntfHelper(L"GetTest", L"GetTest");
    wmcaIntfHelper.registerWndClass(WmcaIntfMsgProc::sampleWndProc);
    wmcaIntfHelper.initInstance();

    HWND hWnd = FindWindowW(0, L"OpenAPI_Test");
    SendMessage(hWnd, WM_COMMAND, 1003, 0);

    wmcaIntfHelper.messageLoop();

    std::wstring str(WmcaIntfMsgProc::sampleData);
    WmcaIntfMsgProc::sampleData.clear();
    return str;
    */
    return std::wstring(L"getTest");
}
