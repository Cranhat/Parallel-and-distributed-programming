#include "Writer.hpp"
#include <iostream>
#include <mutex>
#include <chrono>

#include "Util.hpp"

void Writer::run(){
    while(true){
        state = WriterState::waiting;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(1000, 2000)));
        write();
    }
};

void Writer::write(){
    auto shuffledBooks = books;
    std::shuffle(shuffledBooks.begin(), shuffledBooks.end(), g);
    bool haveWritten = false;
    while (!haveWritten) {
        for (auto& book : shuffledBooks) {
            if (book->tryWrite(state, bookContent)) {
                haveWritten = true;
                break;
            }
        }
        if (!haveWritten) 
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
};

int Writer::getBookContent(){
    return bookContent.content;
}

int Writer::getBookNumber(){
    return bookContent.index;
}