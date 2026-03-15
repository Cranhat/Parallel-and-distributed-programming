#include "DiningRoom.hpp"
#include <iostream>
#include <thread>


void DiningRoom::start(){
    for(auto& philosopher : mPhilosophers){
        mThreads.push_back(std::thread(&Philosopher::run, &philosopher));
    }

};

void DiningRoom::stop(){
    for(int i = 0; i < mPhilosophersNumber; i++){
        mPhilosophers[i].state = stopped;
        mThreads[i].join();
    }
};

void DiningRoom::printStates(){
    for(auto& philospher : mPhilosophers){
        std::cout << "Philosopher " << philospher.mIndex << " " << philospher.getInSimulationState() <<
         " resourceConsumed = " << philospher.resourcesConsumed << std::endl;
    }
}