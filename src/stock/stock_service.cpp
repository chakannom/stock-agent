#include <string>

#include <stock/wmca_intf_helper.hpp>

#include "stock_service.hpp"

std::wstring StockService::getTest() {
	WmcaIntfHelper wmcaIntfHelper;
	std::wstring str = wmcaIntfHelper.getTest(wmcaIntf);
	return str;
}
