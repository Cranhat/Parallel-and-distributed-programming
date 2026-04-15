#include "Logger.hpp"
#include <iostream>


void Logger::log(std::string string){
    access.acquire();
    os << string + "\n";
    access.release();
};
