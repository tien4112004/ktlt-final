#ifndef _STACK_H_
#define _STACK_H
#include "singly_linked_list.h"

struct Stack {
    SNode* top;
};

void initialize(Stack** stack);
bool isEmpty(const Stack* stack);
void push(Stack* stack, int val);
void pop(Stack* stack);
int top(const Stack* stack);
void deinitialize(Stack** stack); 

void initialize(Stack** stack) {
    try {
        *stack = new Stack;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Bad allocation!" << std::endl;
        return;
    }
    catch (std::exception& e) {
        std::cout << "Exception!" << std::endl;
        return;
    }
    (*stack)->top = nullptr;
}

bool isEmpty(const Stack* stack) {
    if (stack->top == nullptr) {
        return true;
    }
    return false;
}

void push(Stack* stack, int val) {
    SNode* new_node = createNode(val);
    if (new_node == nullptr) {
        return;
    }
    new_node->pNext = stack->top;
    stack->top = new_node;
}

void pop(Stack* stack) {
    if (isEmpty(stack)) {
        return;
    }
    SNode* to_be_deleted = stack->top;
    stack->top = to_be_deleted->pNext;
    delete to_be_deleted;
}

int top(const Stack* stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->top->key;
}

void deinitialize(Stack** stack) {
    while (!isEmpty(*stack)) {
        pop(*stack);
    }
    delete *stack;
    *stack = nullptr;
} 

#endif