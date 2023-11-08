#pragma once
#include "queue.h"
#include "stack.h"
#include <iostream>

struct AVL {
    /// @brief defines node struct in AVL tree
    struct AVLNode {
        int key;
        AVLNode* p_left;
        AVLNode* p_right;
        int height;

        int getHeight();
        void setHeight(int h);
        int getBalanceFactor();
        AVLNode* rotateLeft();
        AVLNode* rotateRight();
    };
    AVLNode* pRoot = nullptr;

    AVLNode* createNode(int data);

    void Insert(AVLNode*& pRoot, int x);
    void Insert(int x);
    void Remove(int x);
    // void Remove(AVLNode*& pRoot, int x);

    void NLR();
    // void NLR(AVLNode* pRoot);
    void LNR();
    // void LNR(AVLNode* pRoot);
    void LRN();
    // void LRN(AVLNode* pRoot);
    void LevelOrder();

    struct dataCheck {
        AVLNode* pRoot;
        int min;
        int max;
    };
    bool isAVL();

    void printTree(AVLNode* root, std::string indent = "", bool last = true);

    void copy(AVL tree);
};