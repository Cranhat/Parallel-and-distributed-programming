#include <iostream>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "Table.hpp"

int main(int argc, char** argv)
{
    Table table(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    table.start();

    while(true)
    {
        std::system("clear");
        table.printStates();
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}