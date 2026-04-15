#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <memory>
#include <semaphore>
#include "Logger.hpp"

#define MAX_SEMAPHORE_COUNT 100

enum SmokerState
{
    on,
    off
};

enum InSimulationState
{
    waitingForTamper,
    usingTamper,
    waitingForMatchbox,
    usingMatchbox,
    smoking,
    resting
};

class Smoker
{
    public:
    Smoker(int index, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& tampers, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& matchboxes) 
    : index(index), tampers(tampers), matchboxes(matchboxes){};
    ~Smoker(){
        isOn = false;
        
    }
    void run();
    void getTamper();
    void getMatchbox();
    std::string getInSimulationState(); 

    const int index;
    InSimulationState inSimulationState = waitingForTamper;
    SmokerState state;
    uint64_t cigarettersSmoked = 0; 
    
    private:
        bool isOn = true;
        std::counting_semaphore<MAX_SEMAPHORE_COUNT>& tampers;
        std::counting_semaphore<MAX_SEMAPHORE_COUNT>& matchboxes;
};