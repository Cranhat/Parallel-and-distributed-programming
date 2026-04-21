#include <iostream>
#include <string>
#include <cstdlib>

#include "Library.hpp"

int main(int argc, char* argv[]){
    int readersNumber = 10;
    int writersNumber = 10;
    int booksNumber = 10;
    
    Library library(readersNumber, writersNumber, booksNumber);
    library.start();

    while(true){
        system("cls");
        library.printStates();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    library.stop();
    return 0;
}