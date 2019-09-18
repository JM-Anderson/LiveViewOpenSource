#ifndef CIRCBUFFER_H
#define CIRCBUFFER_H

#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class CircBuffer {
private:
    int cap;
    vector<T> data;

    int readHead = 0;
    int writeHead = 0;
    int numItems = 0;

    void incrementReadHead() {
        readHead = (readHead == cap-1) ? 0 : readHead+1;
    }
    void incrementWriteHead() {
        writeHead = (writeHead == cap-1) ? 0 : writeHead+1;
    }

public:
    CircBuffer(int cap = 0) : cap(cap) {
        data = vector<T>(cap);
    }
    ~CircBuffer() {
        data.clear();
    }

    void add(T item) {
        if (cap == 0)
            throw out_of_range("There is no capacity to add items");

        /* This condition should mean the read and write head are
         * at the same position. Thus we should move the read head
         * forward so it stays aligned with the oldest data */
        if (numItems == cap) {
            incrementReadHead();
        } else {
            /* If we were not at capacity before, the number of
             * items is about to increase */
            numItems++;
        }
        data[writeHead] = item;

        incrementWriteHead();
    }
    T pop() {
        if (numItems == 0)
            throw std::out_of_range("No items in ring buffer");

        T item = data[readHead];
        data[readHead] = T();
        numItems--;

        incrementReadHead();
        return item;
    }

    int getCap() { return cap; }
    int count() { return numItems; }


};

#endif // CIRCBUFFER_H
