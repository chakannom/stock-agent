#pragma once
#include <core/config/thirdparty/cppdb/frontend.hpp>

class StockRepository
{
private:
    cppdb::session stockDB;
public:
    StockRepository();
    ~StockRepository() = default;
    // from Config table
    long getDelayMillisecondsFromConfig();
    // from ListedItem table
    std::vector<std::wstring> getCodesFromListedItem();
};

