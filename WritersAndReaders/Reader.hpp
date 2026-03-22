#pragma once
#include "Book.hpp"
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <memory>
#include <unordered_map>

enum class ReaderState{
    reading,
    waiting
};

class Reader{
public:
    Reader(int index, std::vector<std::shared_ptr<Book>>& books, std::vector<std::condition_variable>& notifiers) 
    : index(index), books(books), notifiers(notifiers), bookContent(-1,-1){};

    void run();
    void read();
    int getBookContent();
    int getBookNumber();

    std::unordered_map<ReaderState, std::string> map = {
        {ReaderState::reading, "reading"},
        {ReaderState::waiting, "waiting"}
    };

    std::thread thread;
    ReaderState state = ReaderState::waiting;
    BookContent bookContent; 
    int index;

    template<typename Person>
    friend std::string getState(Reader reader); 

//private:
    std::vector<std::shared_ptr<Book>>& books;
    std::vector<std::condition_variable>& notifiers;
};