#pragma once

#include <cstdint>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <memory>

#include "Philosopher.hpp"

class DiningRoom
{
    public:
    DiningRoom(uint16_t philosophersNumber) : philosophersNumber(philosophersNumber)
    {
        forks.reserve(philosophersNumber);
        for(int i = 0; i < philosophersNumber; i++)
        {
            forks.emplace_back(std::make_unique<std::mutex>());
        }
        philosophers.reserve(philosophersNumber);
        for(int i = 0; i < philosophersNumber; i++)
        {
            philosophers.emplace_back(Philosopher(i, philosophersNumber, forks));
        }
    };
    ~DiningRoom(){
        stop();
    }

    void start();
    void stop();
    void printStates();

    uint16_t philosophersNumber;
    std::vector<std::thread> threads;
    std::vector<Philosopher> philosophers;
    std::vector<std::unique_ptr<std::mutex>> forks;
};
