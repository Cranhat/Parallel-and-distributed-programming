#include "DiningRoom.hpp"

#include <iostream>
#include <thread>

void DiningRoom::start()
{
    for(auto& philosopher : mPhilosophers)
    {
        mThreads.push_back(std::thread(&Philosopher::run, &philosopher));
    } 
};

void DiningRoom::stop()
{
    for(auto& thread : mThreads)
    {
        thread.join();
    }
};

void DiningRoom::printStates()
{
    for(auto& philospher : mPhilosophers)
    {
        std::cout << "Philosopher " << philospher.index << " " << philospher.getInSimulationState() <<
        " resourceConsumed = " << philospher.resourcesConsumed << std::endl;
    }
}
