#pragma once

#include <stock/wmca_intf.hpp>

class StockService {
private:
	WmcaIntf wmcaIntf;
public:
	StockService();
	~StockService() = default;
	std::wstring getTest();
};

