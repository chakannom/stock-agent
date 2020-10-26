#include <atomic>
#include <iostream>
#include <future>
#include <mutex>
#include <thread>

#include "initializer.hpp"

std::wstring Initializer::url = L"http://localhost:28080/agent";
std::atomic<Initializer*> Initializer::instance;
std::mutex Initializer::initializerMutex;

Initializer::Initializer()
    : stockRest(url), versionRest(url)  {
}

void Initializer::waitAccept() {
    stockRest.accept().wait();
    std::wcout << "Request url for Stock's API: " << stockRest.endpoint() << std::endl;
    versionRest.accept().wait();
    std::wcout << "Request url for Version's API: " << versionRest.endpoint() << std::endl;
}

void Initializer::waitShutdown() {
    stockRest.shutdown().wait();
    versionRest.shutdown().wait();
}