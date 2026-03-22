#include "DiningRoom.hpp"

#include <iostream>
#include <thread>

void DiningRoom::start()
{
    for(auto& philosopher : philosophers)
    {
        threads.push_back(std::thread(&Philosopher::run, &philosopher));
    } 
};

void DiningRoom::stop()
{
    for(auto& thread : threads)
    {
        thread.join();
    }
};

void DiningRoom::printStates()
{
    for(auto& philospher : philosophers)
    {
        std::cout << "Philosopher " << philospher.index << " " << philospher.getInSimulationState() <<
        " resourceConsumed = " << philospher.resourcesConsumed << std::endl;
    }
}
