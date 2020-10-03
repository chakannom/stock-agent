#include <vector>
#include "stock_repository.hpp"

StockRepository::StockRepository() : stockDB("sqlite3:db=stock.db;@pool_size=2") {
}

long StockRepository::getDelayMillisecondsFromConfig() {
    long delayMilliseconds = 0;

    cppdb::result res = stockDB << "SELECT value FROM config WHERE key = 'DELAY_MILLISECONDS_FOR_' || (SELECT value key FROM config WHERE key = 'EXECUTOR_TYPE')" << cppdb::row;
    delayMilliseconds = res.get<long>("value");

    return delayMilliseconds;
}

std::vector<std::wstring> StockRepository::getCodesFromListedItem() {
    std::vector<std::wstring> codes;

    cppdb::result res = stockDB << "SELECT code FROM listed_item";
    while (res.next()) {
        std::string code = res.get<std::string>("code");
        codes.push_back(std::wstring(code.cbegin(), code.cend()));
    }

    return codes;
}