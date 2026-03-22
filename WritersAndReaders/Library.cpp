#include "Library.hpp"
#include <iostream>
#include <thread>

#include "util.hpp"

void Library::start(){
    for(auto& reader : readers)
        mThreads.push_back(std::thread(&Reader::run, &reader));
    
    for(auto& writer : writers)
        mThreads.push_back(std::thread(&Writer::run, &writer));
};

void Library::stop(){
    for(auto& thread : mThreads)
        thread.join();
};

template<typename Person>
void Library::printPersonState(Person& persons, std::string personName){
    for(auto& person : persons){
    std::cout << personName << person.index << " is " ;
    std::string state = getState(person);
    if(state == "waiting")
        std::cout << state << std::endl;
    else    
        std::cout << state << " \"" << person.getBookContent() << "\" in the book nr " << person.getBookNumber()  << std::endl; 
    }
}

void Library::printStates(){
    printPersonState(readers, "Reader ");
    std::cout << "\n";
    printPersonState(writers, "Writer ");
    std::cout << "\n";

    for(auto& book : books){
        std::cout << "Book " << book->getIndex() << " contains \"" << book->getContent() << "\" \n"; 
    }
}