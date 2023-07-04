#include "queue.h"

/// @brief Queue constructor
template<typename T> Queue<T>::Queue() {
    head = nullptr;
    tail = nullptr;
    // cout << "Initiated!";
}
// void copy(Stack A);

/// @brief check if Queue is empty
/// @return true if Queue is empty
template<typename T> bool Queue<T>::empty() {
    return (head == nullptr);
}

/// @brief push a new element to Queue
/// @param key
/// @return true if push successfully
template<typename T> bool Queue<T>::push(T key) {
    Node* new_node;
    try {
        new_node = new Node;
    }
    catch (...) {
        return false;
    }
    new_node->key = key;
    new_node->next = nullptr;

    if (head == nullptr)
        head = new_node;
    else
        tail->next = new_node;
    tail = new_node;
    return true;
}

/// @brief return front value of the Queue
/// @return front value of the Queue
template<typename T> T Queue<T>::front() {
    if (head == nullptr) throw std::runtime_error("Empty queue");
    return head->key;
}

/// @brief pop a value from the Queue
/// @return true if pop successfully
template<typename T> bool Queue<T>::pop() { // bool here is "exit code"
    if (head == nullptr) return false;
    Node* tbd = head;
    head = head->next;
    delete tbd;
    if (head == nullptr) tail = nullptr;
    return true;
}

/// @brief deinitialize Queue
template<typename T> void Queue<T>::deinitialize() {
    Node* cur = head;
    while (cur != nullptr) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
    return;
}

/// @brief print all values in the stack (for debugging)
template<typename T> void Queue<T>::print() {
    for (Node* n = head; n != nullptr; n = n->next) {
        std::cout << n->key << ' ';
    }
}
