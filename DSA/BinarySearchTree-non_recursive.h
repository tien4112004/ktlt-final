#pragma once
#include "queue.h"
#include "stack.h"
#include <iostream>

struct BST {
    struct BSTNode {
        int key;
        BSTNode* p_left;
        BSTNode* p_right;
    };

    BSTNode* pRoot = nullptr;

    BSTNode* createNode(int data);

    // struct privateBST {
    //     static void NLR(BSTNode* pRoot);
    //     static void LNR(BSTNode* pRoot);
    //     static void LRN(BSTNode* pRoot);
    // };

    void NLR();
    void LNR();
    void LRN();
    void LevelOrder();

    BSTNode* Search(int x);
    void Insert(int x);
    void Remove(int x);

    void createTree(int a[], int n);
    void removeTree();

    int Height();
    int countNode();
    int sumNode();
    int heightNode(int value);
    int Level(BSTNode* p);

    int countLeaf();
    int countLess(int x);
    int countGreater(int x);

    struct dataCheck {
        BSTNode* pRoot;
        int min;
        int max;
    };
    // bool isBST(BSTNode* pRoot, int min = -(1 << 30), int max = (1 << 30));
    bool isBST();
    bool isFullBinaryTree(); // helper for isFullBST
    bool isFullBST();

    void copy(BST tree);
};
