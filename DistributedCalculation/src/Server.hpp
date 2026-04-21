#pragma once

#include <sys/types.h>
#include <thread>
#include <vector>
#include <functional>
#include <atomic>

#include "Com_utils.hpp"

class Server{
    public:
    Server(uint processCount) : processCount(processCount){};
    ~Server(){};

    void runServer();

    void createTask(std::function<void(uint, uint)> func, uint from, uint to);
    void divideTasks(std::function<void(uint, uint)> func, uint from, uint to);
    double calculate(std::function<double(uint, uint)> func, uint from, uint to);
    void waitForTasks();
    void updateTimestamp();
    double calculateTimeElapsedInMicroseconds();
    
    private:
    const uint processCount;
    std::vector<std::thread> threads;
    std::chrono::_V2::system_clock::time_point timestamp;
};
