#pragma once

#include <semaphore>
#include <string>
#include <iostream>

class Logger{
    public:
    static Logger& instance(){
        static Logger logger = Logger();
        return logger;
    };

    void log(std::string string);

    private:
    std::binary_semaphore access{1};
    std::ostream& os = std::cout;
};
