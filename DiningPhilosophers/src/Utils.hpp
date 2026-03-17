#pragma once

#include <cstdlib>

inline int generateRandomNumber(int from, int to)
{
    return rand() % (to  - from + 2) + from;
};