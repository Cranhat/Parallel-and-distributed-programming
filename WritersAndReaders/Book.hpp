#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <memory>

enum class ReaderState{
    reading,
    waiting
};

enum class WriterState
{
    writing,
    waiting
};

struct BookContent{
    int index;
    int content;

    BookContent(int i, int c) : index(i), content(c) {}
};

class Book {
public:
    Book(int index) : index(index), content(-1), readNumber(0), readerCount(0), hasBeenWrittenInOnce(false){}

    bool tryWrite(WriterState& state, BookContent& writtenContent);
    bool tryRead(ReaderState& state, BookContent& readContent);

    int getIndex() const { return index; }
    int getContent() const { return content; }
    int getReadNumber() const { return readNumber; }

private:
    int index;
    int content;
    int readNumber;
    int readerCount;
    bool hasBeenWrittenInOnce;
    std::mutex mutex;
    std::mutex resource;
    std::condition_variable notifier;
};