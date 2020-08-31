#include <string>

#include <stock/wmca_intf_helper.hpp>

#include "stock_service.hpp"

StockService::StockService() {
	WmcaIntfHelper::generateWndProcFunctions();
}

std::wstring StockService::getTest() {
	WmcaIntfHelper::sampleData.clear();

	WmcaIntfHelper wmcaIntfHelper(L"GetTest", L"GetTest");
	wmcaIntfHelper.RegisterWndClass(WmcaIntfHelper::sampleWndProc);
	HWND hWnd = wmcaIntfHelper.InitInstance();
	wmcaIntf.Connect(hWnd, CA_WMCAEVENT, 'T', 'W', "", "", "");
	wmcaIntfHelper.messageLoop();

	std::wstring str(WmcaIntfHelper::sampleData);
	WmcaIntfHelper::sampleData.clear();
	return str;
}
