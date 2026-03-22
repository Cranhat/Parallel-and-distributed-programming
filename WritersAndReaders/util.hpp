#pragma once
#include <cstdlib>
#include <unordered_map>
#include <string>

inline int generateRandomNumber(int from, int to){
    return rand() % (to  - from + 2) + from;
};

template<typename Person>
std::string getState(const Person& person){
    return person.map.at(person.state);
}