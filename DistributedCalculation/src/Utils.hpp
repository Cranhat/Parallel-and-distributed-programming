#pragma once
#include <iostream>
typedef unsigned int uint;

inline uint generateRandomNumber(int from, int to)
{
    return rand() % (to  - from + 1) + from;
};
