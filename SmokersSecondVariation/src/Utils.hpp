#pragma once

#include <cstdlib>

inline uint generateRandomNumber(int from, int to)
{
    return rand() % (to  - from + 1) + from;
};
