#include "Agent.hpp"

#include <mutex>
#include "Utils.hpp"



void Agent::run(){
    while(true){
        placeTwoItemsOnTheTable();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        pickUpTwoItemsFromTheTable();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Agent::placeTwoItemsOnTheTable(){
    droppedVariation = generateRandomNumber(1, 3);
    switch (droppedVariation)
    {
    case 1:
        tobacco.release();
        haveTobacco = false;
        matches.release();
        haveMatches = false;
        break;
    case 2:
        paper.release();
        havePaper = false;
        matches.release();
        haveMatches = false;
        break;
    case 3:
        paper.release();
        havePaper = false;
        tobacco.release();
        haveTobacco = false;
        break;
    default:
        break;
    }
}

void Agent::pickUpTwoItemsFromTheTable(){
    switch (droppedVariation)
    {
    case 1:
        tobacco.acquire();
        haveTobacco = true;
        matches.acquire();
        haveMatches = true;
        break;
    case 2:
        paper.acquire();
        havePaper = true;
        matches.acquire();
        haveMatches = true;
        break;
    case 3:
        paper.acquire();
        havePaper = true;
        tobacco.acquire();
        haveTobacco = true;
        break;
    
    default:
        break;
    }
}

