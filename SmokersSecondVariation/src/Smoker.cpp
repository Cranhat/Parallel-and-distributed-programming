#include "Smoker.hpp"

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <chrono>

#include "Utils.hpp"

void Smoker::run()
{
    isOn = 1;
    while(isOn)
    {
        getPaper();
        getTobacco();
        getMatches();
        inSimulationState = assembling;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 100)));
        cigarettesSmoked++;
        inSimulationState = smoking;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 100)));
        releasePaper();
        releaseTobacco();
        releaseMatches();
    }
};

void Smoker::getPaper()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::paper){
        inSimulationState = waitingForPaper;
        paper.acquire();
    }
};

void Smoker::getTobacco()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::tobacco){
        inSimulationState = waitingForTobacco;
        tobacco.acquire();
    }
};

void Smoker::getMatches()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::matches){
        inSimulationState = waitingForMatches;
        matches.acquire();
    }
};
void Smoker::releasePaper()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::paper){
        paper.release();
    }
};

void Smoker::releaseTobacco()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::tobacco){
        tobacco.release();
    }
};

void Smoker::releaseMatches()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::matches){
        matches.release();
    }
};

std::string Smoker::getInSimulationState()
{
    switch(inSimulationState)
    {
        case waitingForTobacco:         return "waitingForTobacco ";   
        case waitingForPaper:           return "waitingForPaper   ";
        case waitingForMatches:         return "waitingForMatches ";
        case assembling:                return "assembling        ";
        case smoking:                   return "smoking           ";
        default:                        return "invalidState      ";
    };
};
