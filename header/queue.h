#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "singly_linked_list.h"

struct Queue {
    SNode* head;
    SNode* tail;
};

void initialize(Queue** queue);
bool isEmpty(const Queue* queue);
void push(Queue* queue, int val);
void pop(Queue* queue);
int front(const Queue* queue);
void deinitialize(Queue** queue);

void initialize(Queue** queue) {
    *queue = new Queue;
    (*queue)->head = nullptr;
    (*queue)->tail = nullptr;
}

bool isEmpty(const Queue* queue) {
    if (queue->head == nullptr) {
        return true;
    }
    return false;
}

void push(Queue* queue, int val) {
    SNode* new_node = createNode(val);
    
    if (isEmpty(queue)) { 
        queue->head = new_node;
    } 
    else {
        queue->tail->pNext = new_node;
    }    
    queue->tail = new_node;
    return;
}

void pop(Queue* queue) {
    if (isEmpty(queue)) {
        return;
    }
    SNode* to_be_deleted = queue->head;
    queue->head = to_be_deleted->pNext;
    if (queue->head == nullptr) {
        queue->tail = nullptr;
    }
    delete to_be_deleted;   
}

int front(const Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    return queue->head->key;
}

void deinitialize(Queue** queue) {
    if (queue == nullptr || isEmpty(*queue)) {
        return;
    }
    SNode* current = (*queue)->head;
    while (current != nullptr) {
        SNode* temp = current;
        current = current->pNext;
        delete temp;
    } 
    // std::cout << "Deinitialized queue.\n";
    delete (*queue);
}


#endif