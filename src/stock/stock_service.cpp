#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include <core/util/string_util.hpp>

#include <stock/wmca_intf_helper.hpp>
#include <stock/wmca_intf_msg_proc.hpp>

#include "stock_service.hpp"

std::wstring StockService::connect(const web::json::value & json) {
    WmcaIntfMsgProc::connectMsg.msg.clear();

    WmcaIntfHelper wmcaIntfHelper(L"connect", L"connect");
    wmcaIntfHelper.registerWndClass(WmcaIntfMsgProc::connectWndProc);
    HWND hWnd = wmcaIntfHelper.initInstance();

    const char* szID = cks::StringUtil::wctoc(json.at(L"id").as_string().c_str());
    const char* szPW = cks::StringUtil::wctoc(json.at(L"pw").as_string().c_str());
    const char* szCertPW = cks::StringUtil::wctoc(json.at(L"certPw").as_string().c_str());
    wmcaIntf.Connect(hWnd, CA_WMCAEVENT, 'T', 'W', szID, szPW, szCertPW);

    wmcaIntfHelper.messageLoop();

    std::wstring msg(WmcaIntfMsgProc::connectMsg.msg);
    WmcaIntfMsgProc::connectMsg.msg.clear();
    return msg;
}

void StockService::disconnect() {

}

void StockService::getBalance() {

}

std::wstring StockService::getTest() {
    WmcaIntfMsgProc::sampleData.clear();

    WmcaIntfHelper wmcaIntfHelper(L"GetTest", L"GetTest");
    wmcaIntfHelper.registerWndClass(WmcaIntfMsgProc::sampleWndProc);
    HWND hWnd = wmcaIntfHelper.initInstance();
    wmcaIntf.Connect(hWnd, CA_WMCAEVENT, 'T', 'W', "", "", "");
    wmcaIntfHelper.messageLoop();

    std::wstring str(WmcaIntfMsgProc::sampleData);
    WmcaIntfMsgProc::sampleData.clear();
    return str;
}
