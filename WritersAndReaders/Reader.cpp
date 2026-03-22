#include "Reader.hpp"
#include <iostream>
#include <mutex>
#include <chrono>

#include "Util.hpp"

void Reader::run(){
    while(true){
        state = ReaderState::waiting;
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(1000, 2000)));
        read();
    }
};

void Reader::read(){
    // auto book = books[0];
    // bookContent = book->read(state, bookContent);

    bool haveRead = false;
    while (!haveRead) {
        for (auto& book : books) {
            if (book->tryRead(state, bookContent)) {
                haveRead = true;
                break;
            }
        }
        if (!haveRead) 
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
};

int Reader::getBookContent(){
    return bookContent.content;
}

int Reader::getBookNumber(){
    return bookContent.index;
}
