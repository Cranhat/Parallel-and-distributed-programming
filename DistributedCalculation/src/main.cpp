#include <iostream>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "Client.hpp"
#include "Server.hpp"
#include <chrono>
#include <cmath>

std::function<double(uint, uint)> EulerFromTo = [](uint from, uint to){
    double sum = 0;
    for(double k = from; k <= to; k++){
        sum += 1.0/k;
    }
    return sum;
};

int main(int argc, char** argv)
{
    // I am a client 
    Server server(8);

    server.updateTimestamp();

    double result = server.calculate(EulerFromTo, 1, 100000000);

    std::cout << "Result = " << result - log(100000000) << " Time elapsed = " << server.calculateTimeElapsedInMicroseconds() << "ms" << std::endl;

}
