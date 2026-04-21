#include <iostream>
#include "Server.hpp"

int main(int argc, char** argv)
{
    Server server(10);
    server.updateTimestamp();
    server.runServer();

    std::cout << server.calculateTimeElapsedInMicroseconds() << "ms" << std::endl;
}
