#include "Smoker.hpp"

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <chrono>

#include "Utils.hpp"

void Smoker::run()
{
    isOn = 1;
    while(isOn)
    {  
        switch (static_cast<uint>(smokerInfiniteResources))
        {
        case  1: // paper
            {
            bool isTobaccoAquired;
            bool isMatchesAquired;
            do{
                isTobaccoAquired = tobacco.try_acquire();
                isMatchesAquired = matches.try_acquire();
                if(isTobaccoAquired)
                    tobacco.release();
                if(isMatchesAquired)
                    matches.release();
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }while(not isTobaccoAquired and not isMatchesAquired);
            break;
            }
        case  2: // tobacco
            {
            bool isPaperAcquired;
            bool isMatchesAquired;
            do{
                isPaperAcquired = paper.try_acquire();
                isMatchesAquired = matches.try_acquire();
                if(isPaperAcquired)
                    paper.release();
                if(isMatchesAquired)
                    matches.release();
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }while(not isPaperAcquired and not isMatchesAquired);
            break;
            }
        case  3: // matches
            {
            bool isPaperAcquired;
            bool isTobaccoAcquired;
            do{
                isPaperAcquired = paper.try_acquire();
                isTobaccoAcquired = tobacco.try_acquire();
                if(isPaperAcquired)
                    paper.release();
                if(isTobaccoAcquired)
                    matches.release();
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }while(not isPaperAcquired and not isTobaccoAcquired);
            break;
        }
        default:
            break;
        }
        inSimulationState = assembling;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 100)));
        cigarettesSmoked++;
        inSimulationState = smoking;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(0, 100)));
        releasePaper();
        releaseTobacco();
        releaseMatches();
    }
};

void Smoker::releasePaper()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::paper){
        paper.release();
    }
};

void Smoker::releaseTobacco()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::tobacco){
        tobacco.release();
    }
};

void Smoker::releaseMatches()
{
    if(smokerInfiniteResources != SmokerInfiniteResources::matches){
        matches.release();
    }
};

// void Smoker::checkIfCanTake(){
//     switch (static_cast<uint>(smokerInfiniteResources))
//     {
//     case  1: // paper
//         // try acquire paper, if can wait
//         paper.acquire();

//         break;
//     case  2: // tobacco
//         // try acquire tobacco, if can wait
//         break;
//     case  3: // matches
//        // try acquire matches, if can wait
//         break;
    
//     default:
//         break;
//     }
// }

std::string Smoker::getInSimulationState()
{
    switch(inSimulationState)
    {
        case waitingForTobacco:         return "waitingForTobacco ";   
        case waitingForPaper:           return "waitingForPaper   ";
        case waitingForMatches:         return "waitingForMatches ";
        case assembling:                return "assembling        ";
        case smoking:                   return "smoking           ";
        default:                        return "invalidState      ";
    };
};
