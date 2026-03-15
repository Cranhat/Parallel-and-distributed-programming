#include "Philosopher.hpp"
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <chrono>

void Philosopher::run(){
    state = started;
    while(true){
        if(gainResource()){
            inSimulationState = resting;
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            inSimulationState = waiting;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(0));
    }
};

bool Philosopher::gainResource(){

    (*forks[mLeftIndex]).lock();
    (*forks[mRightIndex]).lock();
    // if ((*forks[mLeftIndex]).try_lock() == true){
    //     if((*forks[mRightIndex]).try_lock() == false){

    //         std::cv_status status = mNotifiers[mRightIndex].wait_for((*forks[mLeftIndex]), std::chrono::microseconds(10));
    //         if (status == std::cv_status::timeout){
    //             (*forks[mLeftIndex]).unlock();
    //             return false;
    //         }
    //     }
    // }else{
    //     return false;
    // }
    inSimulationState = eating;
    resourcesConsumed++;
    std::this_thread::sleep_for(std::chrono::microseconds(1));

    (*forks[mLeftIndex]).unlock();
    (*forks[mRightIndex]).unlock();

    // mNotifiers[mLeftIndex].notify_one();
    // mNotifiers[mRightIndex].notify_one();

    return true;
};

std::string Philosopher::getInSimulationState(){
    switch(inSimulationState){
        case waiting: return "waiting";   
        case eating: return "eating";
        case resting: return "resting";
        default: return "invalidState";
    };
};