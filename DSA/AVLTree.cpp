#include "AVLTree.h"

/// @brief AVL Tree implementations
namespace AVLTree {
    /// @brief Create new node with key = data
    /// @param data (int) the key to be inserted
    /// @return NODE*: the created node
    NODE* createNode(int data) {
        NODE* new_node;
        try {
            new_node = new NODE{data, nullptr, nullptr, 1};
        }
        catch (...) {
            throw std::runtime_error(
                "Cannot allocate memory! No node created.");
        }

        return new_node;
    }

    /// @brief Find height of a node in tree
    /// @param pRoot (NODE*) the root node
    /// @return int: height of pRoot
    int height(NODE* pRoot) {
        if (pRoot == nullptr) return 0;
        return pRoot->height;
    }

    /// @brief Find balance factor (difference between height(left) and
    /// height(right)) of node.
    /// @param node (NODE*)
    /// @return int: balance factor of node
    int getBalanceFactor(NODE* node) {
        if (node == nullptr) return (1 << 30);
        return height(node->p_right) - height(node->p_left);
    }

    /// @brief left rotate node x
    /// @param x (NODE*) the node need rotate left
    NODE* rotateLeft(NODE* x) {
        if (x == nullptr) return nullptr;
        // std::cout << "\n[rotate left] " << x->key << '\n';
        // change the connections between nodes
        NODE* y = x->p_right;
        x->p_right = y->p_left;
        y->p_left = x;
        // update height
        x->height = std::max(height(x->p_left), height(x->p_right)) + 1;
        y->height = std::max(height(y->p_left), height(y->p_right)) + 1;
        return y;
    }

    /// @brief right rotate node x
    /// @param x (NODE*) the node need rotate right
    NODE* rotateRight(NODE* x) {
        if (x == nullptr) return nullptr;
        // std::cout << "\n[rotate right] " << x->key << '\n';
        NODE* y = x->p_left;
        x->p_left = y->p_right;
        y->p_right = x;
        // update height
        x->height = std::max(height(x->p_left), height(x->p_right)) + 1;
        y->height = std::max(height(y->p_left), height(y->p_right)) + 1;
        return y;
    }

    /// @brief Insert node with UNIQUE key x into pRoot
    /// @param pRoot
    /// @param x
    void Insert(NODE*& pRoot, int x) {
        if (pRoot == nullptr) {
            pRoot = createNode(x);
            return;
        }
        if (x < pRoot->key) { Insert(pRoot->p_left, x); }
        else if (x > pRoot->key) { Insert(pRoot->p_right, x); }
        else
            return; // value duplicated, not add to tree

        pRoot->height
            = 1 + std::max(height(pRoot->p_left), height(pRoot->p_right));
        int balanceFactor = getBalanceFactor(pRoot);
        // std::cout << "[insert] " << pRoot->key << " " << balanceFactor <<
        // '\n';
        if (balanceFactor < -1) {
            if (x < pRoot->p_left->key) {
                pRoot = rotateRight(pRoot);
            } // left-left case
            else if (x > pRoot->p_left->key) {
                pRoot->p_left = rotateLeft(pRoot->p_left);
                pRoot = rotateRight(pRoot);
            } // left-right case
        }
        if (balanceFactor > 1) {
            if (x > pRoot->p_right->key) {
                pRoot = rotateLeft(pRoot);
            } // right-right case
            else if (x < pRoot->p_right->key) {
                pRoot->p_right = rotateRight(pRoot->p_right);
                pRoot = rotateLeft(pRoot);
            } // right-left case
        }
        return;
    }

    /// @brief Remove node has key x from the tree
    /// @param pRoot (NODE*) the root node
    /// @param x (int) the key to be deleted
    void Remove(NODE*& pRoot, int x) {
        if (pRoot == nullptr) return;
        if (x < pRoot->key) { Remove(pRoot->p_left, x); }
        else if (x > pRoot->key) { Remove(pRoot->p_right, x); }
        else {
            if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
                NODE* temp = (pRoot->p_left ? pRoot->p_left : pRoot->p_right);
                if (temp == nullptr) {
                    // std::cout << "[Log] Case 0 - Removed " << pRoot->key
                    //   << ".\n";
                    temp = pRoot;
                    pRoot = nullptr;
                } // pRoot is leaf node
                else {
                    // std::cout << "[Log] Case 1 - Removed " << pRoot->key
                    //           << ".\n";
                    *pRoot = *temp;
                }
                delete temp;
            }
            else {
                // Find successor
                NODE* successor = pRoot->p_right;
                while (successor->p_left != nullptr)
                    successor = successor->p_left;
                // std::cout << "[Log] Case 2 - Removed " << pRoot->key <<
                // ".\n";
                pRoot->key = successor->key;
                Remove(pRoot->p_right, successor->key);
            }
        }

        if (pRoot == nullptr) return;

        // Balancing the tree
        // Update height
        pRoot->height
            = 1 + std::max(height(pRoot->p_left), height(pRoot->p_right));
        int balanceFactor = getBalanceFactor(pRoot);
        if (balanceFactor < -1) {
            if (getBalanceFactor(pRoot->p_left) <= 0) {
                pRoot = rotateRight(pRoot);
            } // left-left case
            else {
                pRoot->p_left = rotateLeft(pRoot->p_left);
                pRoot = rotateRight(pRoot);
            } // left-right case
        }
        if (balanceFactor > 1) {
            if (getBalanceFactor(pRoot->p_right) >= 0) {
                pRoot = rotateLeft(pRoot);
            } // right-right case
            else {
                pRoot->p_right = rotateRight(pRoot->p_right);
                pRoot = rotateLeft(pRoot);
            } // right-left case
        }
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

    /// @brief Check if a tree is a valid AVL tree.
    /// @param pRoot (NODE*) the root of the tree
    /// @param min (int) min valid value of the tree
    /// @param max (int) max valid value of the tree
    /// @return true if pRoot is a valid AVL tree, false otherwise.
    bool isAVL(NODE* pRoot, int min, int max) {
        if (pRoot == nullptr) return true;
        if (pRoot->key < min || pRoot->key > max || getBalanceFactor(pRoot) > 1
            || getBalanceFactor(pRoot) < -1)
            return false;
        return isAVL(pRoot->p_left, min, pRoot->key)
               && isAVL(pRoot->p_right, pRoot->key, max);
    }

    /// @brief Print the tree from root
    /// @param pRoot (NODE*) the root of the tree
    /// @param indent (std::string)
    /// @param last (bool) true
    void printTree(NODE* pRoot, std::string indent, bool last) {
        if (pRoot != nullptr) {
            std::cout << indent;
            if (last == true) {
                std::cout << "R----";
                indent += "   ";
            }
            else {
                std::cout << "L----";
                indent += "|  ";
            }
            std::cout << pRoot->key << '\n';
            printTree(pRoot->p_left, indent, false);
            printTree(pRoot->p_right, indent, true);
        }
    }
} // namespace AVLTree