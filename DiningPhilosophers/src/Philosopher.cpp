#include "Philosopher.hpp"

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <chrono>

#include "Utils.hpp"

void Philosopher::run()
{
    while(true)
    {
        gainResource();
        inSimulationState = resting;
        std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
        inSimulationState = waiting;
        std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
    }
};

void Philosopher::gainResource()
{
    std::lock_guard<std::mutex>(*forks[leftFork]);
    std::lock_guard<std::mutex>(*forks[rightFork]);

    inSimulationState = eating;
    resourcesConsumed++;
    std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
};

std::string Philosopher::getInSimulationState()
{
    switch(inSimulationState)
    {
        case waiting: return "waiting";   
        case eating: return "eating ";
        case resting: return "resting";
        default: return "invalidState";
    };
};