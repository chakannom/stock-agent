#pragma once

#include <stock/stock_rest_controller.hpp>
#include <version/version_rest_controller.hpp>

class Initializer {
private:
    static std::wstring url;
    static std::atomic<Initializer*> instance;
    static std::mutex initializerMutex;

    StockRestController stockRest;
    VersionRestController versionRest;
public:
    static Initializer* getInstance() {
        Initializer* sin = instance.load(std::memory_order_acquire);
        if (!sin) {
            std::lock_guard<std::mutex> myLock(initializerMutex);
            sin = instance.load(std::memory_order_relaxed);
            if (!sin) {
                sin = new Initializer();
                instance.store(sin, std::memory_order_release);
            }
        }
        // volatile int dummy{};
        return sin;
    };
    static void destroyInstance() {
        delete getInstance();
    };
    void waitAccept();
    void waitShutdown();
private:
    Initializer();
    ~Initializer() = default;
    Initializer(const Initializer&) = delete;
    Initializer& operator=(const Initializer&) = delete;
};

