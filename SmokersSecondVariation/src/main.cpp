#include <iostream>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "Table.hpp"

int main(int argc, char** argv)
{
    Table table;

    table.start();
    while(true)
    {
        printf("\033[H\033[J");
        table.printStates();
        table.printAgent();
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}
