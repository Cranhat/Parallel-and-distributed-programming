#include "Server.hpp"
#include <cmath>
#include <iostream>

void Server::createTask(std::function<void(uint, uint)> func, uint from, uint to){
    threads.push_back(std::thread(func, from, to));
};

void Server::divideTasks(std::function<void(uint, uint)> func, uint from, uint to){
    uint i = from;
    uint taskAmount = (to-from + 1)/processCount;
    while(i < to){
        createTask(func, i, std::min((i + taskAmount - 1), to));
        i = i + taskAmount;
    };
};

void Server::waitForTasks(){
    for(auto& th : threads)
        th.join();
}

double Server::calculate(std::function<double(uint, uint)> func, uint from, uint to){
    std::atomic<double> result{0};
    auto extractPartResult = [&](uint from, uint to){
        result.fetch_add(func(from, to));
    };
    divideTasks(extractPartResult, from , to);
    waitForTasks();
    return result;
}

void Server::updateTimestamp(){
    timestamp = std::chrono::system_clock::now();
};

double Server::calculateTimeElapsedInMicroseconds(){
    return double(std::chrono::duration_cast <std::chrono::microseconds> (std::chrono::system_clock::now() - timestamp).count());
};
