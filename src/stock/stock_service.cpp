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

std::wstring StockService::connect(const web::json::value& json) {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    StockServiceHelper stockServiceHelper;

    HWND hWnd = FindWindow(0, L"STOCK_COMMAND");
    SendMessage(hWnd, WM_COMMAND, 1003, 0);

    stockServiceHelper.messageLoop();

    return stockServiceHelper.getData();
    /*
    WmcaIntfMsgProc::connectMsg.msg.clear();

    WmcaIntfHelper wmcaIntfHelper(L"connect", L"connect");
    wmcaIntfHelper.registerWndClass(WmcaIntfMsgProc::connectWndProc);
    wmcaIntfHelper.initInstance();

    const char* szID = cks::StringUtil::wctoc(json.at(L"id").as_string().c_str());
    const char* szPW = cks::StringUtil::wctoc(json.at(L"pw").as_string().c_str());
    const char* szCertPW = cks::StringUtil::wctoc(json.at(L"certPw").as_string().c_str());
    HWND hWnd = FindWindow(0, L"OpenAPI_Test");
    //wmcaIntf.Connect(hWnd, CA_WMCAEVENT, 'T', 'W', szID, szPW, szCertPW);

    SendMessage(hWnd, WM_COMMAND, 1003, 0);

    wmcaIntfHelper.messageLoop();


    std::wstring msg(WmcaIntfMsgProc::connectMsg.msg);
    WmcaIntfMsgProc::connectMsg.msg.clear();
    return msg;
    */
}

void StockService::disconnect() {
    std::lock_guard<std::mutex> lock_guard(stockMutex);
    //if (isConnected()) {
        wmcaIntf.Disconnect();
    //}
}

bool StockService::isConnected() {
    return wmcaIntf.IsConnected();
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
