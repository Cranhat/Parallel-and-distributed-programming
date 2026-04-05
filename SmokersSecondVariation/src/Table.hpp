#pragma once

#include <cstdint>
#include <vector>
#include <thread>
#include <memory>
#include <semaphore>
#include <set>

#include "Smoker.hpp"
#include "Agent.hpp"

class Table
{
    public:
    Table();
    ~Table(){
        stop();
    }

    void start();
    void stop();
    void printStates();
    void printAgent();

    const uint smokersNumber = 3;
    std::vector<std::thread> threads;
    std::vector<Smoker> smokers;
    
    std::counting_semaphore<MAX_SEMAPHORE_COUNT> paper{1};
    std::counting_semaphore<MAX_SEMAPHORE_COUNT> tobacco{1};
    std::counting_semaphore<MAX_SEMAPHORE_COUNT> matches{1};
    Agent agent{paper, tobacco, matches};
};
