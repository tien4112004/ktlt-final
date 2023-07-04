#pragma once
#include <iostream>

template<typename T> class Queue {
    struct Node {
        T key;
        Node* next;
    };
private:
    Node* head;
    Node* tail;
public:
    Queue();
    // void copy(Stack A);

    bool empty();

    bool push(T);

    T front();

    bool pop();

    void deinitialize();

    void print();
};

#include "queue.cpp"