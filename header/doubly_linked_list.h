#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_
#include "../header/header.h"

struct DNode {   
    int key;
    DNode* pNext;
    DNode* pPrev;
};

struct DList {
    DNode* pHead;
    DNode* pTail;
};

void initializeList(DList** w_list);
void deinitialize(DList** w_list);

bool isEmpty(const DList* r_list);

DNode* createNode(int r_value);

DNode* pushFront(DList* u_list, int r_value);
DNode* pushBack(DList* u_list, int r_value);
DNode* insertAfter(DNode* u_node, int r_value);
DNode* insertBefore(DList* list, DNode* u_node, int r_value);

void popFront(DList* u_list);
void popBack(DList* u_list);
void removeAfter(DNode* u_node);
void removeBefore(DList* list, DNode* u_node);

void printList(const DList* list);
DNode* search(const DList* r_list, int r_value);


void initializeList(DList** w_list) {
    try {
        *w_list = new DList{nullptr, nullptr};        
    }
    catch (...) {
        std::cout << "Exception!" << std::endl;
    }

    *w_list = new DList{nullptr, nullptr};
    return;
}

bool isEmpty(const DList* r_list) {
    if (r_list->pHead == nullptr && r_list->pTail == nullptr) {
        return true;
    }
    return false;
}

DNode* createNode(int r_value) {
    DNode* node;
    try {
        node = new DNode{r_value, nullptr, nullptr};
    }
    catch (...) {
        std::cout << "Cannot create new node!" << std::endl;
        return nullptr;
    }
    return node;
}

DNode* pushFront(DList* u_list, int r_value) {
    DNode* node;root
    try {
        node = createNode(r_value);
    }
    catch (...) {
        std::cout << "Cannot create new node!" << std::endl;
        return nullptr;
    }
    if (isEmpty(u_list)) {
        u_list->pHead = u_list->pTail = node;
        return node;
    }
    node->pNext = u_list->pHead;
    u_list->pHead->pPrev = node;
    u_list->pHead = node;
    return node;
}

DNode* pushBack(DList* u_list, int r_value) {
    DNode* node;
    try {
        node = createNode(r_value);
    }
    catch (...) {
        std::cout << "Cannot create new node!\n";
        return nullptr;
    }

    if (isEmpty(u_list)) {
        u_list->pHead = u_list->pTail = node;
        return node;
    }

    u_list->pTail->pNext = node;
    node->pPrev = u_list->pTail;
    u_list->pTail = node;
    return node;
}

DNode* insertAfter(DNode* u_node, int r_value) {
    if (u_node == nullptr) {
        return nullptr;
    }

    DNode* node = createNode(r_value);
    node->pPrev = u_node;
    node->pNext = u_node->pNext;
    u_node->pNext->pPrev = node;
    u_node->pNext = node;

    return node;
}

DNode* insertBefore(DList** list, DNode* u_node, int r_value) {
    if (u_node == nullptr || isEmpty(*list)) {
        return nullptr;
    }
    
    DNode* node = createNode(r_value);
    u_node->pPrev->pNext = node;
    node->pPrev = u_node->pPrev;
    node->pNext = u_node;
    u_node->pPrev = node;

    if (u_node == (*list)->pHead) {
        (*list)->pHead = node;
    }

    return node;
}

void printList(const DList* r_list) {
    DNode* current = r_list->pHead;
    int nodeCount = 0;
    while (current != nullptr) {
        std::cout << '#' << nodeCount << ':' << current << " - key = " 
            << current->key << std::endl;
        nodeCount++;
        current = current->pNext;
    }
}

void DEBUGprintList(const DList* r_list) {
    DNode* current = r_list->pHead;
    int nodeCount = 0;
    while (current != nullptr) {
        std::cout << '#' << nodeCount << ':' << current->pPrev << ' ' <<
             current << ' ' << current->pNext << " - key = " << current->key << std::endl;
        nodeCount++;
        current = current->pNext;
    }
}

void popFront(DList* u_list) {
    if (!u_list || isEmpty(u_list)) {
        return;
    }

    DNode* node = u_list->pHead->pNext;
    delete u_list->pHead;
    u_list->pHead = node;

    if (u_list->pHead == nullptr) {
        u_list->pTail = nullptr;
    }
    else {
        u_list->pHead->pPrev = nullptr;
    }

    return;
}

void popBack(DList* u_list) {
    if (!u_list || isEmpty(u_list)) {
        return;
    }

    DNode* node = u_list->pTail->pPrev;
    delete u_list->pTail;
    u_list->pTail = node;

    if (u_list->pTail == nullptr) {
        u_list->pHead = nullptr;
    }
    else {
        u_list->pTail->pNext = nullptr;
    }

    return;
} 

void removeAfter(DNode* u_node) {
    if (u_node == nullptr || u_node->pNext == nullptr) {
        return;
    }

    DNode* to_be_deleted = u_node->pNext;
    u_node->pNext = to_be_deleted->pNext;
    to_be_deleted->pNext->pPrev = u_node;
    delete to_be_deleted;
    return;
}

void removeBefore(DList* list, DNode* u_node) {
    if (u_node == nullptr || u_node->pPrev == nullptr) {
        return;
    }
    DNode* to_be_deleted = u_node->pPrev;
    to_be_deleted->pPrev->pNext = u_node;
    u_node->pPrev = to_be_deleted->pPrev;
    delete to_be_deleted;
    return;
}


void deinitialize(DList** w_list) {
    if (w_list == nullptr) {
        return;
    }
    if (isEmpty(*w_list)) {
        delete *w_list;
        *w_list = nullptr;
        return;
    }
    DNode* current = (*w_list)->pHead;
    while (current->pNext != nullptr) {
        DNode* node = current;
        current = current->pNext;
        delete node;
    }

    delete *w_list;
    *w_list = nullptr;
    return;
}

DNode* search(const DList* r_list, int r_value) {
    for (DNode* current = r_list->pHead; current != nullptr; current = current->pNext) {
        if (current->key == r_value) 
            return current;
    }

    printf("Cannot find element has provided key!");
    return nullptr;
    // throw std::runtime_error("Cannot find element has provided key!");
}

#endif