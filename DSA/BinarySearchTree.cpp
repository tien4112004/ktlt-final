#include "BinarySearchTree.h"

/// @brief Binary Search Tree implementations
namespace BinarySearchTree {
    /// @brief Create new node with key = data
    /// @param data (int)
    /// @return NODE*: new node
    NODE* createNode(int data) {
        NODE* new_node;
        try {
            new_node = new NODE{data, nullptr, nullptr};
        }
        catch (...) {
            throw std::runtime_error("Cannot allocate memory.");
        }

        return new_node;
    }

    /// @brief Preorder traversal
    /// @param pRoot (NODE*) the root of the tree
    void NLR(NODE* pRoot) {
        if (pRoot == nullptr) return;

        std::cout << pRoot->key << ' ';
        NLR(pRoot->p_left);
        NLR(pRoot->p_right);
        return;
    }

    /// @brief Inorder traversal
    /// @param pRoot (NODE*) the root of the tree
    void LNR(NODE* pRoot) {
        if (pRoot == nullptr) return;

        LNR(pRoot->p_left);
        std::cout << pRoot->key << ' ';
        LNR(pRoot->p_right);
        return;
    }

    /// @brief Postorder traversal
    /// @param pRoot (NODE*) the root of the tree
    void LRN(NODE* pRoot) {
        if (pRoot == nullptr) return;

        LRN(pRoot->p_left);
        LRN(pRoot->p_right);
        std::cout << pRoot->key << ' ';
        return;
    }

    /// @brief Level order traversal, using BFS
    /// @param pRoot (NODE*) the root of the tree
    void LevelOrder(NODE* pRoot) {
        if (pRoot == nullptr) return;

        Queue<NODE*> q;
        NODE* current = pRoot;
        q.push(current);
        int level = 0;
        while (!q.empty()) {
            Queue<NODE*> temp;
            std::cout << level << ": ";
            while (!q.empty()) {
                NODE* current = q.front();
                std::cout << current->key << ' ';
                q.pop();
                if (current->p_left != nullptr) temp.push(current->p_left);
                if (current->p_right != nullptr) temp.push(current->p_right);
            }
            std::cout << '\n';
            q = temp;
            level++;
        }
        return;
    }

    /// @brief Search the node with key x
    /// @param pRoot (NODE*) the root of the tree
    /// @param x (int) the key need to search
    /// @return NODE*
    NODE* Search(NODE* pRoot, int x) {
        if (pRoot == nullptr) return nullptr;

        if (pRoot->key == x) return pRoot;

        if (x < pRoot->key) return Search(pRoot->p_left, x);
        if (x > pRoot->key) return Search(pRoot->p_right, x);
        return nullptr;
    }

    /// @brief Insert a new node into tree pRoot
    /// @param pRoot (NODE*) the root of the tree
    /// @param x (int) to be inserted key
    void Insert(NODE*& pRoot, int x) {
        if (pRoot == nullptr) {
            pRoot = createNode(x);
            return;
        }

        if (x < pRoot->key) { Insert(pRoot->p_left, x); }
        else { Insert(pRoot->p_right, x); }
    }

    /// @brief Remove the node with key x from the tree
    /// @param pRoot (NODE*) the root of the tree
    /// @param x to be removed key
    void Remove(NODE*& pRoot, int x) {
        if (pRoot == nullptr) return;

        NODE* parent = pRoot;
        NODE* current = pRoot;

        while (current != nullptr && current->key != x) {
            parent = current;
            if (x < current->key)
                current = current->p_left;
            else if (x > current->key)
                current = current->p_right;
        }

        // Node with key x not found
        if (current == nullptr) {
            std::cout << "[Log] Not found! No removal have been made!\n";
            return;
        }

        // Case 1: leaf node
        if (current->p_left == nullptr && current->p_right == nullptr) {
            if (parent->p_left == current)
                parent->p_left = nullptr;
            else
                parent->p_right = nullptr;
            delete current;
            return;
        }

        // Case 2: has 1 child
        if (current->p_left == nullptr || current->p_right == nullptr) {
            NODE* child = (current->p_left != nullptr ? current->p_left
                                                      : current->p_right);
            if (parent->p_left == current)
                parent->p_left = child;
            else
                parent->p_right = child;
            delete current;
            return;
        }

        // Case 2: has 2 child
        // Find successor (or predecessor)
        NODE* successor = current->p_right;
        NODE* successor_parent = current;
        while (successor->p_left != nullptr) {
            successor_parent = successor;
            successor = successor->p_left;
        }

        if (successor_parent->p_left == successor)
            successor_parent->p_left = successor->p_right;
        else { successor_parent->p_right = successor->p_right; }

        current->key = successor->key;
        delete successor;
        std::cout << "[Log] Removed " << x << ".\n";

        return;
    }

    /// @brief Create a binary search tree with the given key array
    /// @param a (int[]) the key array
    /// @param n (int) size of a[]
    /// @return NODE*: root of created BST
    NODE* createTree(int a[], int n) {
        if (n == 0) return nullptr;
        NODE* pRoot = createNode(a[0]);
        for (int i = 1; i < n; i++) { Insert(pRoot, a[i]); }
        return pRoot;
    }

    /// @brief Remove all nodes of the tree, set the root node to nullptr
    /// @param pRoot (NODE*) the root of the tree
    void removeTree(NODE*& pRoot) {
        if (pRoot == nullptr) return;

        removeTree(pRoot->p_left);
        removeTree(pRoot->p_right);
        delete pRoot;

        pRoot = nullptr;

        return;
    }

    /// @brief Calculate height
    /// @param pRoot (NODE*) the root of the tree
    /// @return height of the tree
    int Height(NODE* pRoot) {
        if (pRoot == nullptr) return 0;
        return std::max(Height(pRoot->p_left), Height(pRoot->p_right)) + 1;
    }

    /// @brief Count node of the tree
    /// @param pRoot (NODE*) the root of the tree
    /// @return The number of nodes of the tree
    int countNode(NODE* pRoot) {
        if (pRoot == nullptr) return 0;
        return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
    }

    /// @brief Calculate sum of keys of nodes in the tree
    /// @param pRoot (NODE*) the root of the tree
    /// @return sum of keys
    int sumNode(NODE* pRoot) {
        if (pRoot == nullptr) return 0;
        return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
    }

    // actually "depth" of node in ANY BINARY TREE
    /// @brief Return level of the node in the tree
    /// @param pRoot (NODE*) the root of the tree
    /// @param p (NODE*) the node that need to find level
    /// @return int: level of the node
    int Level(NODE* pRoot, NODE* p) {
        if (pRoot == nullptr) { return -1; }

        if (pRoot == p) return 1;

        int left = Level(pRoot->p_left, p);
        if (left != -1) return left + 1;

        int right = Level(pRoot->p_right, p);
        if (right != -1) return right + 1;

        return -1;
    }

    /// @brief Find height of the node has key x in the tree
    /// @param pRoot (NODE*) the root of the tree
    /// @param value
    /// @return int: height of the node
    int heightNode(NODE* pRoot, int value) {
        NODE* current = Search(pRoot, value);
        return Height(current);
    }

    /// @brief Count the number of leaf nodes in the tree
    /// @param pRoot (NODE*) the root of the tree
    /// @return int: the number of leaf nodes
    int countLeaf(NODE* pRoot) {
        if (pRoot == nullptr) return 0;
        if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;

        return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
    }

    /// @brief Count the number of nodes that its key less than x
    /// @param pRoot (NODE*) the root of the tree
    /// @param x
    /// @return int: the number of nodes that its key less than x
    int countLess(NODE* pRoot, int x) {
        if (pRoot == nullptr) return 0;

        int count = 0;
        if (x > pRoot->key) {
            count = 1 + countLess(pRoot->p_left, x)
                    + countLess(pRoot->p_right, x);
        }
        else { count = countLess(pRoot->p_left, x); }

        return count;
    }

    /// @brief Count the number of nodes that its key greater than x
    /// @param pRoot (NODE*) the root of the tree
    /// @param x
    /// @return int: the number of nodes that its key less than x
    int countGreater(NODE* pRoot, int x) {
        if (pRoot == nullptr) return 0;

        int count = 0;
        if (x < pRoot->key)
            count = 1 + countGreater(pRoot->p_right, x)
                    + countGreater(pRoot->p_left, x);
        else
            count = countGreater(pRoot->p_right, x);

        return count;
    }

    /// @brief Check if a tree is a BST or not
    /// @param pRoot (NODE*) the root of the tree
    /// @param min (int) min valid value of the tree
    /// @param max (int) max valid value of the tree
    /// @return true if that tree is BST, false otherwise
    bool isBST(NODE* pRoot, int min, int max) {
        if (pRoot == nullptr) return true;
        if (pRoot->key > max || pRoot->key < min) return false;

        bool left = isBST(pRoot->p_left, min, pRoot->key);
        bool right = isBST(pRoot->p_right, pRoot->key, max);
        return left && right;
    }

    /// @brief Check if a tree is full binary tree
    /// @param pRoot (NODE*) the root of the tree
    /// @return true if that tree is a FBT, false otherwise
    bool isFullBinaryTree(NODE* pRoot) {
        if (pRoot == nullptr) return true;
        if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
            return true;
        }
        if (pRoot->p_left && pRoot->p_right) {
            return isFullBinaryTree(pRoot->p_left)
                   && isFullBinaryTree(pRoot->p_right);
        }

        return false;
    }

    /// @brief Check if a tree is a full BST
    /// @param pRoot (NODE*) the root of the tree
    /// @return true if that tree is a full BST, false otherwise
    bool isFullBST(NODE* pRoot) {
        return isBST(pRoot) && isFullBinaryTree(pRoot);
    }
} // namespace BinarySearchTree
