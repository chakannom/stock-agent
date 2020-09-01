#include <string>

#include <stock/wmca_intf_helper.hpp>
#include <stock/wmca_intf_msg_proc.hpp>

#include "stock_service.hpp"

std::wstring StockService::connect() {
	WmcaIntfMsgProc::connectMsg.msg.clear();

	WmcaIntfHelper wmcaIntfHelper(L"connect", L"connect");
	wmcaIntfHelper.registerWndClass(WmcaIntfMsgProc::connectWndProc);
	HWND hWnd = wmcaIntfHelper.initInstance();

	wmcaIntf.Connect(hWnd, CA_WMCAEVENT, 'T', 'W', "", "", "");

	wmcaIntfHelper.messageLoop();

	std::wstring msg(WmcaIntfMsgProc::connectMsg.msg);
	WmcaIntfMsgProc::connectMsg.msg.clear();
	return msg;
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
