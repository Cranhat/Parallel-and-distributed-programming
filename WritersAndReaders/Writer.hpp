#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <memory>
#include <unordered_map>
#include "Book.hpp"

enum class WriterState
{
    writing,
    waiting
};

class Writer
{
public:
    Writer(int index, std::vector<std::shared_ptr<Book>>& books, std::vector<std::condition_variable>& notifiers) 
    : index(index), books(books), notifiers(notifiers), bookContent(-1,-1){};

    void run();
    void write();
    int getBookContent();
    int getBookNumber();

    std::unordered_map<WriterState, std::string> map = {
        {WriterState::writing, "writing"},
        {WriterState::waiting, "waiting"}
    };

    std::thread thread;
    WriterState state = WriterState::waiting;
    int index;

    template<typename Person>
    friend std::string getState(Writer writer); 

private:
    BookContent bookContent;
    std::vector<std::shared_ptr<Book>>& books;
    std::vector<std::condition_variable>& notifiers;
};