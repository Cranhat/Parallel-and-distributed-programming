#pragma once

#include <cstdlib>
#include <chrono>

inline uint generateRandomNumber(int from, int to)
{
    return rand() % (to  - from + 1) + from;
};
