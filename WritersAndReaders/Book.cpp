#include "Book.hpp"
#include "util.hpp"

BookContent Book::write() {
    std::unique_lock<std::mutex> lock(mutex);

    if(hasBeenWrittenInOnce)
        notifier.wait(lock, [this]() {  return readNumber >= 3; });

    resource.lock();
    lock.unlock();

    int numberToWrite = generateRandomNumber(0, 100);
    content = numberToWrite;
    BookContent writtenContent(index, numberToWrite);
    hasBeenWrittenInOnce = true;

    std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));

    resource.unlock();

    lock.lock();
    readNumber = 0;
    lock.unlock();

    notifier.notify_all();

    return writtenContent;
}

BookContent Book::read() {
    std::unique_lock<std::mutex> lock(mutex);
    notifier.wait(lock, [this]() {  return hasBeenWrittenInOnce;   });

    readerCount++;
    if (readerCount >= 1) resource.lock();
    lock.unlock();
    
    BookContent readContent(index, content);
    std::this_thread::sleep_for(std::chrono::microseconds(generateRandomNumber(0, 1000)));

    lock.lock();
    readerCount--;
    readNumber++;
    if (readerCount == 0) resource.unlock();
    lock.unlock();
    notifier.notify_all();

    return readContent;
}

void Book::blockFromWriting(){
    if(readerCount > 0)
        resource.lock();
}

void Book::unblockFromWriting(){
    if(readerCount == 0)
        resource.unlock();
}