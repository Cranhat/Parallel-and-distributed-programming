#include "Book.hpp"
#include "util.hpp"

bool Book::tryWrite(WriterState& state, BookContent& writtenContent) {
    std::unique_lock<std::mutex> lock(mutex,  std::try_to_lock);
    if (!lock || (readNumber < 3 && hasBeenWrittenInOnce)) 
        return false;

    // if(hasBeenWrittenInOnce)
    //     notifier.wait(lock, [this]() {  return readNumber >= 3; });

    resource.lock();

    content = generateRandomNumber(0, 100);
    writtenContent.index = index;
    writtenContent.content = content;
    readNumber = 0;
    hasBeenWrittenInOnce = true;
    state = WriterState::writing;
    std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(1000, 3000)));

    resource.unlock();
    lock.unlock();
    notifier.notify_all();

    return true;
}

bool Book::tryRead(ReaderState& state, BookContent& readContent) {
    std::unique_lock<std::mutex> lock(mutex,  std::try_to_lock);
    if (!lock || !hasBeenWrittenInOnce) 
        return false;

    //notifier.wait(lock, [this]() {  return hasBeenWrittenInOnce;   });
    readerCount++;
    if (readerCount == 1) 
        resource.lock();
    lock.unlock();

    state = ReaderState::reading;
    readContent.index = index;
    readContent.content = content;
    std::this_thread::sleep_for(std::chrono::milliseconds(generateRandomNumber(1000, 2000)));

    lock.lock();
    readerCount--;
    readNumber++;
    if (readerCount == 0) 
        resource.unlock();
    lock.unlock();
    notifier.notify_all();

    return true;
}