#include "stack.h"

/// @brief Stack constructor
template<typename T> Stack<T>::Stack() {
    top = nullptr;
    // cout << "Initiated!";
};

// void copy(Stack A);

/// @brief check if Stack is empty
/// @return true if Stack is empty
template<typename T> bool Stack<T>::empty() {
    return (top == nullptr);
}

/// @brief push a new element to Stack
/// @param key
/// @return true if push successfully
template<typename T> bool Stack<T>::push(T key) {
    Node* new_node;
    try {
        new_node = new Node;
    }
    catch (...) {
        return false;
    }
    new_node->key = key;
    new_node->next = top;
    top = new_node;
    return true;
};

/// @brief return top value of the stack
/// @return top value of the stack: int
template<typename T> T Stack<T>::front() {
    if (top == nullptr) return -(1 << 30);
    return top->key;
};

/// @brief pop a value from the stack
/// @return true if pop successfully
template<typename T> bool Stack<T>::pop() {
    if (top == nullptr) return false;
    Node* tbd = top;
    top = top->next;
    delete tbd;
    return true;
};

/// @brief deinitialize Stack
template<typename T> void Stack<T>::deinitialize() {
    Node* cur = top;
    while (cur != nullptr) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }

    top = nullptr;
    return;
};