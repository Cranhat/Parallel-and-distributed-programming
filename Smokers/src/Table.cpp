#include "Table.hpp"

#include <iostream>
#include <thread>
#include <string>

void Table::start()
{
    for(auto& smoker : smokers)
    {
        threads.push_back(std::thread(&Smoker::run, std::ref(smoker)));
    } 
};

void Table::stop()
{
    for(auto& thread : threads)
    {
        thread.join();
    }
};

void Table::printStates()
{
    for(auto& smoker : smokers)
    {   
        logger.log("Smoker " + std::to_string(smoker.index) + " " + smoker.getInSimulationState() + " resourceConsumed = " + std::to_string(smoker.cigarettersSmoked));
    }
}
