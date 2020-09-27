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
        std::wstring requestMessage = reqJson.serialize();

        web::json::value resJson = getResponseJson(requestMessage.c_str(), IDC_BTN_CONNECT);

        return resJson.serialize();
    }
    else {
        // 연결 중 호출한 경우 같은 데이터 전달
    }
}

//------------------------------------------------------------------
std::wstring StockService::disconnect() {
    if (isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);

        web::json::value resJson = getResponseJson(nullptr, IDC_BTN_DISCONNECT);

        return resJson.serialize();
    }
    else {
        // 연결 중이 아닌데 호출한 경우 연결 해제된 상태임을 알려주는 데이터 전달
    }
}

//------------------------------------------------------------------
bool StockService::isConnected() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);

    web::json::value resJson = getResponseJson(nullptr, IDC_BTN_ISCONNECTED);

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
        std::wstring requestMessage = L"{ \"code\": \"" + code + L"\"}";

        web::json::value resJson = getResponseJson(requestMessage.c_str(), IDC_BTN_INQUIRECURRENTPRICE);

        return resJson.serialize();
    }
    else {
        // 연결 중이 아닌데 호출한 경우 연결이 필요하다는 데이터 전달
    }
}

//------------------------------------------------------------------
void StockService::getBalance() {

}

web::json::value StockService::getResponseJson(const wchar_t* pRequestMessage, DWORD btnId) {
    StockServiceHelper stockServiceHelper;

    HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR");

    if (pRequestMessage != nullptr && wcslen(pRequestMessage) > 0) {
        COPYDATASTRUCT cds;
        cds.dwData = WM_STOCK_EXECUTOR_SETSTRINGVARIABLE;
        cds.cbData = wcslen(pRequestMessage) * sizeof(wchar_t);
        cds.lpData = (PVOID)pRequestMessage;

        SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&cds);
    }

    SendMessage(hWnd, WM_COMMAND, btnId, 0);

    stockServiceHelper.messageLoop();

    std::wstring data = stockServiceHelper.getData();
    // LOG.DEBUG(data) 넣기..
    return web::json::value::parse(data);
}

//------------------------------------------------------------------
std::wstring StockService::getTest() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    //std::wstring code = L"한국";
    //std::wstring requestMessage = L"{ \"code\": \"" + code + L"\"}";

    //web::json::value resJson = getResponseJson(requestMessage.c_str(), IDC_BTN_ISCONNECTED);
    return std::wstring(L"getTest");
}
