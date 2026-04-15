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
        inSimulationState = waitingForTamper;
        getTamper();
        inSimulationState = waitingForMatchbox;
        getMatchbox();
        inSimulationState = smoking;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 50)));
        cigarettersSmoked++;
        inSimulationState = resting;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 50)));
    }
};

void Smoker::getTamper()
{
    tampers.acquire();
    inSimulationState = usingTamper;
    std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 50)));
    tampers.release();
};

void Smoker::getMatchbox()
{
    matchboxes.acquire();
    inSimulationState = usingMatchbox;
    std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 50)));
    matchboxes.release();
};

std::string Smoker::getInSimulationState()
{
    switch(inSimulationState)
    {
        case waitingForTamper:      return "waitingForTamper  ";   
        case usingTamper:           return "usingTamper       ";
        case waitingForMatchbox:    return "waitingForMatchbox";
        case usingMatchbox:         return "usingMatchbox     ";
        case smoking:               return "smoking           ";
        case resting:               return "resting           ";
        default:                    return "invalidState      ";
    };
};
