#include "Table.hpp"

#include <iostream>
#include <thread>

Table::Table(){
    smokers.reserve(smokersNumber);
    for(uint i = 0; i < smokersNumber; i++)
    {
        smokers.emplace_back(Smoker(i, static_cast<SmokerInfiniteResources>(i), paper, tobacco, matches));
    } 
};

void Table::start()
{
    threads.push_back(std::thread(&Agent::run, std::ref(agent)));
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
        std::cout << "Smoker " << smoker.index << " Age: " << smoker.getInSimulationState() <<
        " resourceConsumed = " << smoker.cigarettesSmoked << " inf res: " << smoker.smokerInfiniteResources << std::endl;
    }
}

void Table::printAgent()
{
    std::cout << "agent dropped variation: " << agent.droppedVariation << " paper: " << agent.havePaper << " tobacco: " << agent.haveTobacco << " matches: " << agent.haveMatches << std::endl;
}
