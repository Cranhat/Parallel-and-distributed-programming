#pragma once

#include <cstdint>
#include <vector>
#include <thread>
#include <memory>
#include <semaphore>

#include "Smoker.hpp"
#include "Logger.hpp"

class Table
{
    public:
    Table(uint16_t smokersNumber, uint16_t tampersCount, uint16_t matchboxesCount) :
    smokersNumber(smokersNumber),
    tampersCount(tampersCount),
    matchboxesCount(matchboxesCount),
    tampers{tampersCount},
    matchboxes{matchboxesCount}
    {
        for(int i = 0; i < smokersNumber; i++)
        {
            smokers.push_back(Smoker(i, tampers, matchboxes));
        }
        
    };
    ~Table(){
        stop();
    }

    void start();
    void stop();
    void printStates();

    uint16_t smokersNumber;
    uint16_t tampersCount;
    uint16_t matchboxesCount;
    std::vector<std::thread> threads;
    std::vector<Smoker> smokers;
    std::counting_semaphore<MAX_SEMAPHORE_COUNT> tampers;
    std::counting_semaphore<MAX_SEMAPHORE_COUNT> matchboxes;

    Logger& logger = Logger::instance();
};
