#pragma once

#include <cstdlib>

int generateRandomNumber(int from, int to){
    return rand() % (to  - from + 2) + from;
};