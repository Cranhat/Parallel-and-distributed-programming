#pragma once

#include <cstdint>
#include <vector>
#include <thread>
#include <memory>
#include <semaphore>

#include "Smoker.hpp"


// Smoker(int index, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& rammers, std::counting_semaphore<MAX_SEMAPHORE_COUNT>& matchboxes) 
//     : index(index), rammers(rammers), matchboxes(matchboxes){};

class Table
{
    public:
    Table(uint16_t smokersNumber, uint16_t rammersCount, uint16_t matchboxesCount) :
    smokersNumber(smokersNumber),
    rammersCount(rammersCount),
    matchboxesCount(matchboxesCount),
    rammers{rammersCount},
    matchboxes{matchboxesCount}
    {
        smokers.reserve(smokersNumber);
        for(int i = 0; i < smokersNumber; i++)
        {
            smokers.emplace_back(Smoker(i, rammers, matchboxes));
        }
        
    };
    ~Table(){
        stop();
    }
    void start();
    void stop();
    void printStates();

    uint16_t smokersNumber;
    uint16_t rammersCount;
    uint16_t matchboxesCount;
    std::vector<std::thread> threads;
    std::vector<Smoker> smokers;
    std::counting_semaphore<MAX_SEMAPHORE_COUNT> rammers;
    std::counting_semaphore<MAX_SEMAPHORE_COUNT> matchboxes;

};
