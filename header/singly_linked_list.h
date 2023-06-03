#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

// u = update
// r = read
// w = write

struct SNode {
    int key;
    SNode* pNext; // sizeof(any pointer) = 8 (64-bit) = const;
};

struct SList {
    SNode* pHead;
    SNode* pTail;
};


void initializeList(SList** w_list);
void deinitialize(SList** w_list);

bool isEmpty(const SList* r_list);

SNode* createNode(int value);

SNode* pushFront(SList* u_list, int r_value);
SNode* pushBack(SList* u_list, int r_value);
SNode* insertAfter(SNode* u_node, int r_value);
SNode* insertBefore(SList* *list, SNode* u_node, int r_value);

void popFront(SList* u_list);
void popBack(SList* u_list);
void removeAfter(SNode* u_node);
void removeBefore(SList* *list, SNode* u_node);

void printList(const SList* *list);
SNode* search(const SList* r_list, int r_value);

void merge(SList* u_list_a, SList* u_list_b);
void swapList(SList* u_list_a, SList* u_list_b);
void reverseList(SList* u_list);
SNode* reverseList_Recursive(SNode* head);

// Merge sort components
void splitList(SNode* source, SNode** front, SNode** back);
SNode* mergeSortedList(SNode* node_a, SNode* node_b);
void MergeSort(SNode** head);


void initializeList(SList** w_list) {
    try {
        *w_list = new SList;
    }
    catch (std::bad_alloc& e){
        std::cout << "Bad allocation!" << std::endl;
        return;
    }
    catch (std::exception& e) {
        std::cout << "Exception!" << std::endl;
        return;
    }
    catch (...) {
        std::cout << "Unknown error!" << std::endl;
        return;
    }


    (*w_list)->pHead = nullptr;
    (*w_list)->pTail = nullptr;
    // OR
    // *w_list = new SList(nullptr, nullptr);
}

/*
// other ways:
void initializeList(SList*& w_list) {
    w_list->pHead = nullptr;
    w_list->pTail = nullptr;
}

void initializeLst(SList& w_list) {
    w_list.pHead = w_list.pTail = nullptr;
}

SList* initializeList() {
    return new SList{nullptr, nullptr};
}
*/

bool isEmpty(const SList* r_list) {
    if (r_list->pHead == nullptr && r_list->pTail == nullptr) {
        return true;
    }
    return false;
}

SNode* createNode(int value) {
    SNode* node;  
    try {
        node = new SNode;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Bad allocation!" << std::endl;
        return nullptr;
    }
    catch (std::exception& e) {
        std::cout << "Exception!" << std::endl;
        return nullptr;
    }
    catch (...) {
        std::cout << "Unknown error!" << std::endl;
        return nullptr;
    }
    node->key = value;
    node->pNext = nullptr;

    return node;

    // OR
    // return new SNode{value, nullptr};
}

SNode* pushFront(SList* u_list, int r_value) {
    SNode* node;
    try {
        node = createNode(r_value);
    }
    catch (...) {
        printf("Cannot create new node!");
        return nullptr;
    }
    node->pNext = u_list->pHead;
    u_list->pHead = node;
    if (u_list->pTail == nullptr) {
        u_list->pTail = node; 
    }

    return node;
}

SNode* pushBack(SList* u_list, int r_value) {
    SNode* node;
    try {
        node = createNode(r_value);
    }
    catch (...) {
        printf("Cannot create new node!");
        return nullptr;
    
    if (isEmpty(u_list)) {
        u_list->pHead = u_list->pTail = node;
    }
    u_list->pTail->pNext = node;
    u_list->pTail = node;

    return node;
}

SNode* insertAfter(SNode* u_node, int r_value) { // u = update
    if (u_node == nullptr) {    
        return nullptr;
    }
    SNode* node;
    try {
        node = createNode(r_value);
    }        
    catch(...) {
        std::cout << "Cannot create new node!" << std::endl;
        return nullptr;
    }
    node->pNext = u_node->pNext;
    u_node->pNext = node;

    return node;
}

// Insert node -> đảo giá trị
SNode* insertBefore(SList** list, SNode* u_node, int r_value) {
    if (u_node == nullptr || isEmpty(*list)) {
        return nullptr;
    }

    if (u_node == (*list)->pHead) {
        return pushFront(*list, r_value);
    }

    SNode* current = (*list)->pHead;
    while (current->pNext != u_node || current->pNext == nullptr) {
        current = current->pNext;
    }   
    return insertAfter(current, r_value);
}

void popFront(SList* u_list) {
    if (isEmpty(u_list) == true)
        return;

    SNode* node = u_list->pHead;
    u_list->pHead = node->pNext;
    if (u_list->pHead == nullptr) {
        u_list->pTail = nullptr;
    }
    delete node;

    return;
}

void popBack(SList* u_list) {
    if (isEmpty(u_list) || u_list == nullptr) {
        return;
    }
    // Find the node before tail
    SNode* node_before_tail = u_list->pHead;
    while (node_before_tail->pNext != u_list->pTail) {
        node_before_tail = node_before_tail->pNext;
    }

    delete u_list->pTail;
    node_before_tail->pNext = nullptr;
    u_list->pTail = node_before_tail;
    if (u_list->pTail == nullptr) {
        u_list->pHead = nullptr;
    }
}

void removeAfter(SNode* u_node) {
    if (u_node == nullptr) 
        return;
    SNode* node = u_node->pNext;
    u_node->pNext = u_node->pNext->pNext;
    delete node;
}

void removeBefore(SList* *list, SNode* u_node) {
    SNode* current = (*list)->pHead;
    while(current->pNext->pNext != u_node) {
        current = current->pNext;
    }
    removeAfter(current);
}

void printList(const SList* r_list) {
    SNode* node = r_list->pHead;
    int nodeCount = 0;
    while (node != nullptr) {
        nodeCount++;
        printf("#%d - Node %lld - value = %d\n", nodeCount, node, node->key);
        node = node->pNext;
    }
    printf("\n");
    // OR
    // for (SNode* node = r_list->pHead; node != nullptr; node = node->pNext) {
        // printf("Node %lld - value = %d\n", node, node->key);
    // }
}

SNode* search(const SList* r_list, int r_value) {
    for (SNode* current = r_list->pHead; current != nullptr; current = current->pNext) {
        if (current->key == r_value) 
            return current;
    }

    printf("Cannot find element has provided key!");
    return nullptr;
    // throw std::runtime_error("Cannot find element has provided key!");
}

void deinitialize(SList** w_list) {
    if (*w_list == nullptr) {
        return;
    }
    if ((*w_list)->pHead == nullptr) {
        delete *w_list; 
        *w_list = nullptr;
        return;
    }    
    SNode* current = (*w_list) ->pHead;
    while (current) {
        SNode* temp = current;
        current = current->pNext;
        delete temp;
    }
    delete *w_list;
    *w_list = nullptr;
}

//////////////////////
void merge(SList* u_list_a, SList* u_list_b) {
    u_list_a->pTail->pNext = u_list_b->pHead;
    u_list_a->pTail = u_list_b->pTail;
    u_list_b->pHead = nullptr;
    u_list_b->pTail = nullptr;
}


void swapList(SList* u_list_a, SList* u_list_b) {
    SNode* temp = u_list_a->pHead;
    u_list_a->pHead = u_list_b->pHead;
    u_list_b->pHead = temp;

    temp = u_list_a->pTail;
    u_list_a->pTail = u_list_b->pTail;
    u_list_b->pTail = temp;
}


void reverseList(SList* u_list) {
    SNode* current = u_list->pHead;
    SNode* previous = nullptr;
    SNode* next = nullptr;

    while(current != nullptr) {
        next = current->pNext;
        current->pNext = previous;
        previous = current;
        current = next;
    }

    u_list->pHead = previous;
    SNode* node = u_list->pHead;
    while(node->pNext != nullptr) {
        node = node->pNext;
    }

    u_list->pTail = node;

    return;
}

SNode* reverseList_Recursive(SNode* head) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->pNext == nullptr) {
        return head;
    }`

    SNode* node = reverseList_Recursive(head->pNext);
    node->pNext = head;
    head->pNext = nullptr;
    return head;
}

void splitList(SNode* source, SNode** front, SNode** back) {
    SNode* fast = source->pNext;
    SNode* slow = source;

    while (fast != nullptr) {
        fast = fast->pNext;
        if (fast != nullptr) {
            fast = fast->pNext;
            slow = slow->pNext;
        }
    }

    *front = source;
    *back = slow->pNext;
    slow->pNext = nullptr;
    return;
}

SNode* mergeSortedList(SNode* node_a, SNode* node_b) {
    if (node_a == nullptr) return node_b;
    if (node_b == nullptr) return node_a;

    SNode* result = nullptr;

    if (node_a->key <= node_b->key) {
        result = node_a;
        result->pNext = mergeSortedList(node_a->pNext, node_b);
    } else {
        result = node_b;
        result->pNext = mergeSortedList(node_a, node_b->pNext);
    }

    return result;
}

void MergeSort(SNode** head) {
    SNode* node = *head;
    SNode* front = nullptr;
    SNode* back = nullptr;

    if (node->pNext == nullptr) return;

    splitList(node, &front, &back);
    MergeSort(&front);
    MergeSort(&back);

    *head = mergeSortedList(front, back);
}

#endif