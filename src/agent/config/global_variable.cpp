#include "global_variable.hpp"

std::atomic<GlobalVariable*> GlobalVariable::instance;
std::mutex GlobalVariable::myMutex;