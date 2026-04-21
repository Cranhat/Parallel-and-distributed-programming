#include "Server.hpp"
#include <cmath>
#include <iostream>

std::function<double(uint, uint)> EulerFromTo = [](uint from, uint to){
    double sum = 0;
    for(double k = from; k <= to; k++){
        sum += 1.0/k;
    }
    return sum;
};

void Server::createTask(std::function<void(uint, uint)> func, uint from, uint to){
    threads.push_back(std::thread(func, from, to));
};

void Server::divideTasks(std::function<void(uint, uint)> func, uint from, uint to){
    uint i = from;
    uint taskAmount = (to-from + 1)/processCount;
    if(taskAmount == 0) taskAmount = 1;
    while(i <= to){
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
    threads.clear();
    result = result - log(to);
    return result;
}

void Server::updateTimestamp(){
    timestamp = std::chrono::system_clock::now();
};

double Server::calculateTimeElapsedInMicroseconds(){
    return double(std::chrono::duration_cast <std::chrono::microseconds> (std::chrono::system_clock::now() - timestamp).count());
};

void Server::runServer() {
    initSockets();

    socket_t serverSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(54000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSock, (sockaddr*)&addr, sizeof(addr));
    listen(serverSock, 5);

    std::cout << "Server up\n";

    while (true) {
        socket_t client = accept(serverSock, nullptr, nullptr);

        std::thread([client, this]() {

            while (true) {
                char buffer[1024]{};
                int bytes = recv(client, buffer, sizeof(buffer) - 1, 0);

                if (bytes <= 0) {
                    break;
                }

                buffer[bytes] = '\0';

                uint n = std::stoul(buffer);

                this->updateTimestamp();
                double result = this->calculate(EulerFromTo, 1, n);

                std::string response = std::to_string(result);

                send(client, response.c_str(), response.size(), 0);
            }

            closeSocket(client);
        }).detach();
    }

    cleanupSockets();
}