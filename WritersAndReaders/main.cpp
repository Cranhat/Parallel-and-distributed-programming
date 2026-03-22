#include <iostream>
#include <string>
#include <cstdlib>

#include "Library.hpp"

int main(int argc, char* argv[]){
    int readersNumber = 2;
    int writersNumber = 2;
    int booksNumber = 1;
    
    Library library(readersNumber, writersNumber, booksNumber);
    library.start();

    while(true){
        system("cls");
        library.printStates();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    library.stop();
    return 0;
}