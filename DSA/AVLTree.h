#pragma once

#include "queue.h"
#include <iostream>

namespace AVLTree {
    struct NODE {
        int key;
        NODE* p_left;
        NODE* p_right;
        int height;
    };

    NODE* createNode(int data);

    int balanceFactor(NODE* a, NODE* b);
    NODE* rotateLeft(NODE* x);
    NODE* rotateRight(NODE* x);
    void Insert(NODE*& pRoot, int x);
    void Remove(NODE*& pRoot, int x);

    void NLR(NODE* pRoot);
    void LNR(NODE* pRoot);
    void LRN(NODE* pRoot);
    void LevelOrder(NODE* pRoot);

    bool isAVL(NODE* pRoot, int min = -(1 << 30), int max = (1 << 30));

    void printTree(NODE* root, std::string indent = "", bool last = true);
} // namespace AVLTree