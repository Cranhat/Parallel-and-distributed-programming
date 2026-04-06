#include "Smoker.hpp"

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <chrono>

#include "Utils.hpp"

void Smoker::run()
{
    isOn = true;
    while(isOn)
    {
        inSimulationState = waitingForRammer;
        getRammer();
        inSimulationState = waitingForMatchbox;
        getMatchbox();
        inSimulationState = smoking;
        std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
        cigarettersSmoked++;
        inSimulationState = resting;
        std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
    }
};

void Smoker::getRammer()
{
    rammers.acquire();
    inSimulationState = usingRammer;
    std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
    rammers.release();
};

void Smoker::getMatchbox()
{
    matchboxes.acquire();
    inSimulationState = usingMatchbox;
    std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
    matchboxes.release();
};

std::string Smoker::getInSimulationState()
{
    switch(inSimulationState)
    {
        case waitingForRammer:      return "waitingForRammer  ";   
        case usingRammer:           return "usingRammer       ";
        case waitingForMatchbox:    return "waitingForMatchbox";
        case usingMatchbox:         return "usingMatchbox     ";
        case smoking:               return "smoking           ";
        case resting:               return "resting           ";
        default:                    return "invalidState      ";
    };
};
