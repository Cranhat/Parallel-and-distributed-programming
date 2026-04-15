#include <iostream>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "Table.hpp"
#include "Logger.hpp"

int main(int argc, char** argv)
{
    Logger& logger = Logger::instance();
    Table table(10, 3, 3);
    // Table table(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    table.start();

    while(true)
    {
        logger.log("\x1B[2J\x1B[H");
        table.printStates();
        std::this_thread::sleep_for(std::chrono::microseconds(1666));
    }
}