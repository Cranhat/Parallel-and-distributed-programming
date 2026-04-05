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

class Agent
{
    public:
    Agent(std::counting_semaphore<MAX_SEMAPHORE_COUNT>& paper, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& tobacco, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& matches)
    : paper(paper), tobacco(tobacco), matches(matches)
    {
        paper.acquire();
        havePaper = true;
        tobacco.acquire();
        haveTobacco = true;
        matches.acquire();
        haveMatches = true;
    };
    ~Agent() = default;

    void run();
    void placeTwoItemsOnTheTable();
    void pickUpTwoItemsFromTheTable();

    uint droppedVariation = 0;

    bool havePaper = false;
    bool haveTobacco = false;
    bool haveMatches = false;

    std::counting_semaphore<MAX_SEMAPHORE_COUNT>& paper;
    std::counting_semaphore<MAX_SEMAPHORE_COUNT>& tobacco;
    std::counting_semaphore<MAX_SEMAPHORE_COUNT>& matches;
};
