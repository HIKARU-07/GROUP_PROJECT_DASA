#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../models/BookingRequest.h"
#include <stdexcept>

using namespace std;

class PriorityQueue {
private:
    BookingRequest* heap;
    int capacity;
    int size;

    bool higherPriority(
        const BookingRequest& a,
        const BookingRequest& b
    ) const {

        if (a.getTimestamp() != b.getTimestamp()) {
            return a.getTimestamp() < b.getTimestamp();
        }

        return a.getRequestId() < b.getRequestId();
    }

    void swapRequest(
        BookingRequest& a,
        BookingRequest& b
    ) {
        BookingRequest temp = a;
        a = b;
        b = temp;
    }

    void heapifyUp(int index) {

        while (index > 0) {

            int parent = (index - 1) / 2;

            if (!higherPriority(
                    heap[index],
                    heap[parent])) {
                break;
            }

            swapRequest(
                heap[index],
                heap[parent]
            );

            index = parent;
        }
    }

    void heapifyDown(int index) {

        while (true) {

            int left = index * 2 + 1;
            int right = index * 2 + 2;

            int smallest = index;

            if (
                left < size &&
                higherPriority(
                    heap[left],
                    heap[smallest])
            ) {
                smallest = left;
            }

            if (
                right < size &&
                higherPriority(
                    heap[right],
                    heap[smallest])
            ) {
                smallest = right;
            }

            if (smallest == index) {
                break;
            }

            swapRequest(
                heap[index],
                heap[smallest]
            );

            index = smallest;
        }
    }

    void resize() {

        int newCapacity = capacity * 2;

        BookingRequest* newHeap =
            new BookingRequest[newCapacity];

        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }

        delete[] heap;

        heap = newHeap;
        capacity = newCapacity;
    }

public:

    PriorityQueue(int initialCapacity = 16) {

        capacity = initialCapacity;
        size = 0;

        heap =
            new BookingRequest[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    void push(const BookingRequest& request) {

        if (size == capacity) {
            resize();
        }

        heap[size] = request;

        size++;

        heapifyUp(size - 1);
    }

    BookingRequest top() const {

        if (size == 0) {
            throw runtime_error(
                "PriorityQueue is empty"
            );
        }

        return heap[0];
    }

    void pop() {

        if (size == 0) {
            throw runtime_error(
                "PriorityQueue is empty"
            );
        }

        heap[0] = heap[size - 1];

        size--;

        if (size > 0) {
            heapifyDown(0);
        }
    }

    bool empty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};

#endif