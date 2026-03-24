#pragma once

#include <cstdint>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <memory>

#include "Reader.hpp"
#include "Writer.hpp"
#include "Book.hpp"

class Library{
    public:
    Library(int readersNumber, int writersNumber, int booksNumber) : readersNumber(readersNumber), 
    writersNumber(writersNumber), booksNumber(booksNumber)
    {
        books.reserve(booksNumber);
        for(int i = 0; i < booksNumber; i++)
            books.emplace_back(std::make_shared<Book>(i));
        
        readers.reserve(readersNumber);
        for(int i = 0; i < readersNumber; i++)
            readers.emplace_back(i, books);
        
        writers.reserve(writersNumber);
        for(int i = 0; i < writersNumber; i++)
            writers.emplace_back(i, books);
        
    };

    void start();
    void stop();
    template<typename Person>
    void printPersonState(Person& persons, std::string personName);
    void printStates();
    

    int readersNumber;
    int writersNumber;
    int booksNumber;
    std::vector<std::thread> mThreads;
    std::vector<Reader> readers;
    std::vector<Writer> writers;
    std::vector<std::shared_ptr<Book>> books;
};