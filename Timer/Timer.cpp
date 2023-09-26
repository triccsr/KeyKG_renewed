//
// Created by triccsr on 9/16/23.
//

#include <chrono>
#include "Timer.h"

int64_t Timer::milli_stamp() {
    int64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch())
            .count();
    return ms;
}

int64_t  Timer::micro_stamp() {
    int64_t us = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now().time_since_epoch())
            .count();
    return us;
}