#define _UNICODE
#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>
#include "stock_service.hpp"
#include <core/util/string_util.hpp>
#include <stock/stock_service_helper.hpp>

StockService::StockService() {
    delayMilliseconds = stockRepository.getDelayMillisecondsFromConfig();
}

//------------------------------------------------------------------
/** 
 * RequestJson Format:
 * {
 *      "id" : "username",
 *      "pw" : "password",
 *      "certPw" : "certificate password"
 * }
 */
web::json::value StockService::connect(const web::json::value& reqJson) {
    if (!isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);
        std::wstring requestMessage = reqJson.serialize();

        web::json::value resJson = getResponseJson(requestMessage.c_str(), IDC_BTN_CONNECT);
        if (!resJson.at(L"code").as_string()._Equal(L"00000")) {
            // resJson.at(L"message").as_string(); 과 함께 에러 발생 처리
        }

        return resJson.at(L"data");
    }
    else {
        // 연결 중 상태임을 알려주는 데이터 전달
    }
}

//------------------------------------------------------------------
bool StockService::disconnect() {
    if (isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);

        web::json::value resJson = getResponseJson(nullptr, IDC_BTN_DISCONNECT);

        return true;
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
web::json::value StockService::getCurrentPriceOfItems() {
    if (isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);
        web::json::value items = web::json::value::array();
        int i = 0;

        std::vector<std::wstring> codes = stockRepository.getCodesFromListedItem();
        for (std::wstring code : codes) {
            std::wstring requestMessage = L"{ \"code\": \"" + code + L"\"}";
            // 가져온 데이터로 조건 검색 추가할 것
            // 검색에 맞는 것만 resJson에 넣음
            web::json::value resJson = getResponseJson(requestMessage.c_str(), IDC_BTN_INQUIRECURRENTPRICE);
            if (!resJson.at(L"code").as_string()._Equal(L"00000")) {
                // resJson.at(L"message").as_string(); 과 함께 에러 발생 처리
            }
            if (resJson.has_field(L"data")) {
                items[i++] = resJson.at(L"data");
            }
        }

        return items;
    }
    else {
        // 연결 중이 아닌데 호출한 경우 연결이 필요하다는 데이터 전달
    }
}

//------------------------------------------------------------------
/**
 * RequestJson Format:
 * {
 *      "code" : "000000"
 * }
 */
web::json::value StockService::getCurrentPriceOfItem(std::wstring& code) {
    if (isConnected()) {
        std::lock_guard<std::mutex> lock_guard(stockMutex);
        web::json::value item = web::json::value::object();

        std::wstring requestMessage = L"{ \"code\": \"" + code + L"\"}";
        web::json::value resJson = getResponseJson(requestMessage.c_str(), IDC_BTN_INQUIRECURRENTPRICE);
        if (!resJson.at(L"code").as_string()._Equal(L"00000")) {
            // resJson.at(L"message").as_string(); 과 함께 에러 발생 처리
        }
        if (resJson.has_field(L"data")) {
            item = resJson.at(L"data");
        }

        return item;
    }
    else {
        // 연결 중이 아닌데 호출한 경우 연결이 필요하다는 데이터 전달
    }
}

//------------------------------------------------------------------
void StockService::getBalance() {

}

//------------------------------------------------------------------
web::json::value StockService::getResponseJson(const wchar_t* pRequestMessage, DWORD btnId) {
    clock_t startedMilliseconds = clock();

    StockServiceHelper stockServiceHelper;

    HWND hWnd = FindWindowW(0, L"STOCK-EXECUTOR");

    if (pRequestMessage != nullptr && wcslen(pRequestMessage) > 0) {
        COPYDATASTRUCT cds;
        cds.dwData = WM_STOCK_EXECUTOR_SETSTRINGVARIABLE;
        cds.cbData = (DWORD)wcslen(pRequestMessage) * sizeof(wchar_t);
        cds.lpData = (PVOID)pRequestMessage;

        SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&cds);
    }

    SendMessage(hWnd, WM_COMMAND, btnId, 0);

    stockServiceHelper.messageLoop();

    std::wstring data = stockServiceHelper.getData();
    // LOG.DEBUG(data) 넣기..

    clock_t endedMilliseconds = clock();
    long durationMilliseconds = endedMilliseconds - startedMilliseconds;
    long remainedMilliseconds = delayMilliseconds - durationMilliseconds;
    if (remainedMilliseconds > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(remainedMilliseconds));
    }

    return web::json::value::parse(data);
}

//------------------------------------------------------------------
std::wstring StockService::getTest() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    //std::wstring code = L"한국";
    //std::wstring requestMessage = L"{ \"code\": \"" + code + L"\"}";

    //web::json::value resJson = getResponseJson(requestMessage.c_str(), IDC_BTN_ISCONNECTED);

    web::json::value resJson = web::json::value::array();
    /*
    cppdb::result res = stockDB << "SELECT id,code,name FROM listed_item";

    int i = 0;
    while (res.next()) {
        int id;
        std::string code;
        std::string name;
        res >> id >> code >> name;

        resJson[i][L"code"] = web::json::value::string(std::wstring(code.cbegin(), code.cend()));
        resJson[i][L"name"] = web::json::value::string(cks::StringUtil::utf8ToUnicode(name));

        i++;
    }
    */
    return resJson.serialize();
}
