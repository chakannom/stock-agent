#pragma once
#include <atomic>
#include <iostream>
#include <future>
#include <mutex>
#include <thread>
#include <windows.h>

class GlobalVariable {
private:
    HWND hwnd;
public:
    static GlobalVariable* getInstance() {
        GlobalVariable* sin = instance.load(std::memory_order_acquire);
        if (!sin) {
            std::lock_guard<std::mutex> myLock(myMutex);
            sin = instance.load(std::memory_order_relaxed);
            if (!sin) {
                sin = new GlobalVariable();
                instance.store(sin, std::memory_order_release);
            }
        }
        // volatile int dummy{};
        return sin;
    }
    HWND getHwnd() {
        return this->hwnd;
    }
    void setHwnd(HWND hwnd) {
        this->hwnd = hwnd;
    }
private:
    GlobalVariable() = default;
    ~GlobalVariable() = default;
    GlobalVariable(const GlobalVariable&) = delete;
    GlobalVariable& operator=(const GlobalVariable&) = delete;

    static std::atomic<GlobalVariable*> instance;
    static std::mutex myMutex;
};