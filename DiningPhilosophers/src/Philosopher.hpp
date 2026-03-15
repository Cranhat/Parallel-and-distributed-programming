#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <memory>

enum State {
    stopped,
    started
};

enum InSimulationState{
    waiting,
    eating,
    resting
};

class Philosopher {
    public:
    Philosopher(int index, int maxIndex, std::vector<std::unique_ptr<std::mutex>>& forks, std::vector<std::condition_variable>& notifiers) : mIndex(index), mMaxIndex(maxIndex), forks(forks), mNotifiers(notifiers){};

    void run();

    bool gainResource();
    std::string getInSimulationState(); 
    State state = started;
    std::thread thread;
    int mIndex;
    InSimulationState inSimulationState = waiting;
    uint64_t resourcesConsumed = 0; 
    private:
        int mMaxIndex;
        int mLeftIndex = mIndex;
        int mRightIndex = (mIndex + 1) % mMaxIndex;


        std::vector<std::unique_ptr<std::mutex>>& forks;
        std::vector<std::condition_variable>& mNotifiers;
};