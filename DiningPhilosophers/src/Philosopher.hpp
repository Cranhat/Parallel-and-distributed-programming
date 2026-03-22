#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <memory>

enum InSimulationState
{
    waiting,
    eating,
    resting
};

class Philosopher
{
    public:
    Philosopher(int index, int maxIndex, std::vector<std::unique_ptr<std::mutex>>& forks) 
    : index(index), maxIndex(maxIndex), forks(forks){};

    void run();
    void gainResource();

    std::string getInSimulationState(); 
    std::thread thread;
    InSimulationState inSimulationState = waiting;
    uint64_t resourcesConsumed = 0; 
    int index;

    private:
        std::vector<std::unique_ptr<std::mutex>>& forks;
        int maxIndex;
        // reverse if last index
        int leftFork = (index + 1) == maxIndex ? (index + 1) % maxIndex : index;
        int rightFork = (index + 1) == maxIndex ? index : (index + 1) % maxIndex;
};