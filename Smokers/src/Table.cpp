#include "Table.hpp"

#include <iostream>
#include <thread>

void Table::start()
{
    for(auto& smoker : smokers)
    {
        threads.push_back(std::thread(&Smoker::run, &smoker));
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
        std::cout << "Smoker " << smoker.index << " " << smoker.getInSimulationState() <<
        " resourceConsumed = " << smoker.cigarettersSmoked << std::endl;
    }
}
