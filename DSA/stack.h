#pragma once
#include <iostream>
using namespace std;

template<typename T> class Stack {
    struct Node {
        T key;
        Node* next;
    };
private:
    Node* top;
public:
    Stack();
    // void copy(Stack A);

    bool empty();

    bool push(T);

    T front();

    bool pop();

    void deinitialize();
};

#include "stack.cpp"