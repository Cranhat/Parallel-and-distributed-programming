#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <memory>
#include <semaphore>
#include "Utils.hpp"

#define MAX_SEMAPHORE_COUNT 100

enum InSimulationState
{
    waitingForPaper,
    waitingForTobacco,
    waitingForMatches,
    assembling,
    smoking
};

enum SmokerInfiniteResources
{
    paper,
    tobacco,
    matches
};

class Smoker
{
    public:
    Smoker(uint index, SmokerInfiniteResources smokerInfiniteResources, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& paper, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& tobacco, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& matches) 
    : index(index), smokerInfiniteResources(smokerInfiniteResources), paper(paper), tobacco(tobacco),  matches(matches)
    {
    };

    void run();
    std::string getInSimulationState(); 
    void releasePaper();
    void releaseTobacco();
    void releaseMatches();
    
    const uint index;
    uint cigarettesSmoked = 0; 
    SmokerInfiniteResources smokerInfiniteResources;

    private:
        bool isOn = false;
        std::counting_semaphore<MAX_SEMAPHORE_COUNT>& paper;
        std::counting_semaphore<MAX_SEMAPHORE_COUNT>& tobacco;
        std::counting_semaphore<MAX_SEMAPHORE_COUNT>& matches;
        InSimulationState inSimulationState = waitingForPaper;
};
