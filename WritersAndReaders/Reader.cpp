#include "Reader.hpp"
#include <iostream>
#include <mutex>
#include <chrono>

#include "Util.hpp"

void Reader::run(){
    while(true){
        read();
        state = ReaderState::waiting;
        std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
    }
};

void Reader::read(){
    state = ReaderState::reading;
    auto book = books[0];
    bookContent = book->read();
    std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));
};

int Reader::getBookContent(){
    return bookContent.content;
}

int Reader::getBookNumber(){
    return bookContent.index;
}
