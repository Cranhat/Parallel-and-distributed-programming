#include <iostream>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "DiningRoom.hpp"

int main(int argc, char* argv[])
{
    DiningRoom diningRoom(5);
    diningRoom.start();

    while(true)
    {
        std::system("clear");
        diningRoom.printStates();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}