#pragma once
#include "queue.h"
#include <iostream>

namespace BinarySearchTree {
    struct NODE {
        int key;
        NODE* p_left;
        NODE* p_right;
    };

    NODE* createNode(int data);

    void NLR(NODE* pRoot);
    void LNR(NODE* pRoot);
    void LRN(NODE* pRoot);
    void LevelOrder(NODE* pRoot);

    NODE* Search(NODE* pRoot, int x);
    void Insert(NODE*& pRoot, int x);
    void Remove(NODE*& pRoot, int x);

    NODE* createTree(int a[], int n);
    void removeTree(NODE*& pRoot);

    int Height(NODE* pRoot);
    int countNode(NODE* pRoot);
    int sumNode(NODE* pRoot);
    int heightNode(NODE* pRoot, int value);
    int Level(NODE* pRoot, NODE* p);

    int countLeaf(NODE* pRoot);
    int countLess(NODE* pRoot, int x);
    int countGreater(NODE* pRoot, int x);

    bool isBST(NODE* pRoot, int min = -(1 << 30), int max = (1 << 30));
    bool isFullBinaryTree(NODE* pRoot); // helper for isFullBST
    bool isFullBST(NODE* pRoot);
} // namespace BinarySearchTree
