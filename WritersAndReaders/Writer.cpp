#include "Writer.hpp"
#include <iostream>
#include <mutex>
#include <chrono>

#include "Util.hpp"

void Writer::run(){
    while(true){
        write();
        state = WriterState::waiting;
        std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
    }
};

void Writer::write(){
    state = WriterState::writing;
    auto book = books[0];
    bookContent = book->write();
    std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
};

int Writer::getBookContent(){
    return bookContent.content;
}

int Writer::getBookNumber(){
    return bookContent.index;
}