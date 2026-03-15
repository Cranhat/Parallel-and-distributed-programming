#pragma once

#include <cstdint>
#include "Philosopher.hpp"
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <memory>


class DiningRoom {
    public:
    DiningRoom(uint16_t philosophersNumber) : mPhilosophersNumber(philosophersNumber){
        mPhilosophers.reserve(mPhilosophersNumber);
        forks.reserve(mPhilosophersNumber);
        for(int i = 0; i < mPhilosophersNumber; i++){
            mPhilosophers.emplace_back(Philosopher(i, mPhilosophersNumber, forks, notifiers));
            forks.emplace_back(std::make_unique<std::mutex>());
        }
    };

    void start();
    void stop();
    void printStates();

    uint16_t mPhilosophersNumber;
    std::vector<std::thread> mThreads;
    std::vector<Philosopher> mPhilosophers;
    std::vector<std::unique_ptr<std::mutex>> forks;
    std::vector<std::condition_variable> notifiers;
};