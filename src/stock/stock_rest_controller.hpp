#pragma once

#include <core/controller/basic_controller.hpp>

#include <stock/stock_service.hpp>

class StockRestController : public cfx::BasicController, cfx::Controller {
private:
    StockService stockService;
public:
    StockRestController(const std::wstring& url);
    ~StockRestController() = default;
private:
    void initRestOpHandlers() override;
    void handleGet(http_request request) override;
    void handlePut(http_request request) override;
    void handlePost(http_request request) override;
    void handlePatch(http_request request) override;
    void handleDelete(http_request request) override;
    void handleHead(http_request request) override;
    void handleOptions(http_request request) override;
    void handleTrace(http_request request) override;
    void handleConnect(http_request request) override;
    void handleMerge(http_request request) override;
};
