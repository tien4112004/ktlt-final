#include "BinarySearchTree.h"

/// @brief Create new node with key = data
/// @param data (int)
/// @return BSTNode*: new node
BST::BSTNode* BST::createNode(int data) {
    BST::BSTNode* new_node;
    try {
        new_node = new BST::BSTNode{data, nullptr, nullptr};
    }
    catch (...) {
        throw std::runtime_error("Cannot allocate memory.");
    }

    return new_node;
}

// /// @brief Preorder traversal
// /// @param pRoot (BSTNode*) the root of the tree
// void BST::NLR(BST::BSTNode* pRoot) {
//     if (pRoot == nullptr) return;

//     std::cout << pRoot->key << ' ';
//     NLR(pRoot->p_left);
//     NLR(pRoot->p_right);
//     return;
// }

/// @brief Preorder traversal non-recursive
void BST::NLR() {
    // NLR(this->pRoot);
    if (pRoot == nullptr) return;
    Stack<BSTNode*> s;
    s.push(pRoot);
    BSTNode* current = pRoot;
    while (!s.empty()) {
        current = s.front();
        s.pop();
        std::cout << current->key << ' ';
        if (current->p_right) s.push(current->p_right);
        if (current->p_left) s.push(current->p_left);
    }

    return;
}

// /// @brief Inorder traversal
// /// @param pRoot (BSTNode*) the root of the tree
// void BST::LNR(BST::BSTNode* pRoot) {
//     if (pRoot == nullptr) return;

//     BST::LNR(pRoot->p_left);
//     std::cout << pRoot->key << ' ';
//     BST::LNR(pRoot->p_right);
//     return;
// }

/// @brief Inorder traversal non-recursive
void BST::LNR() {
    // BST::LNR(this->pRoot);
    if (pRoot == nullptr) return;
    Stack<BSTNode*> s;
    BSTNode* current = pRoot;
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->p_left;
        }
        current = s.front();
        s.pop();
        std::cout << current->key << ' ';
        current = current->p_right;
    }

    return;
}

// /// @brief Postorder traversal
// /// @param pRoot (BSTNode*) the root of the tree
// void BST::LRN(BST::BSTNode* pRoot) {
//     if (pRoot == nullptr) return;

//     BST::LRN(pRoot->p_left);
//     BST::LRN(pRoot->p_right);
//     std::cout << pRoot->key << ' ';
//     return;
// }

/// @brief Postorder traversal non-recursive
void BST::LRN() {
    // BST::LRN(this->pRoot);
    if (pRoot == nullptr) return;

    Stack<BSTNode*> s;
    BSTNode* current = pRoot;
    BSTNode* last_visited = nullptr;
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->p_left;
        }
        current = s.front();
        if (current->p_right == nullptr || current->p_right == last_visited) {
            std::cout << current->key << ' ';
            last_visited = current;
            current = nullptr;
            s.pop();
        }
        else
            current = current->p_right;
    }
}

/// @brief Level order traversal, using BFS
void BST::LevelOrder() {
    if (pRoot == nullptr) return;

    Queue<BST::BSTNode*> q;
    BST::BSTNode* current = pRoot;
    q.push(current);
    int level = 0;
    while (!q.empty()) {
        Queue<BST::BSTNode*> temp;
        std::cout << level << ": ";
        while (!q.empty()) {
            BST::BSTNode* current = q.front();
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
/// @param x (int) the key need to search
/// @return BSTNode*
BST::BSTNode* BST::Search(int x) {
    BSTNode* current = pRoot;
    while (current != nullptr) {
        if (current->key == x) return current;

        if (current->key < x)
            current = current->p_right;
        else
            current = current->p_left;
    }
    return nullptr;
}

/// @brief Insert a new node into tree pRoot
/// @param x (int) to be inserted key
void BST::Insert(int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }

    BSTNode* current = pRoot;
    while (current != nullptr) {
        if (current->key == x) {
            std::cout << "[Log] " << x << " already exists!\n";
            return;
        }

        if (current->key < x) {
            if (current->p_right == nullptr) {
                current->p_right = createNode(x);
                return;
            }
            current = current->p_right;
        }
        else {
            if (current->p_left == nullptr) {
                current->p_left = createNode(x);
                return;
            }
            current = current->p_left;
        }
    }
}

/// @brief Remove the node with key x from the tree
/// @param x (int) to be removed key
void BST::Remove(int x) {
    if (pRoot == nullptr) return;

    BST::BSTNode* parent = pRoot;
    BST::BSTNode* current = pRoot;

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
        // tree has only 1 node
        if (parent == current) {
            delete current;
            pRoot = nullptr;
            return;
        }

        if (parent->p_left == current)
            parent->p_left = nullptr;
        else
            parent->p_right = nullptr;
        delete current;
        return;
    }

    // Case 2: has 1 child
    if (current->p_left == nullptr || current->p_right == nullptr) {
        BST::BSTNode* child
            = (current->p_left != nullptr ? current->p_left : current->p_right);
        if (parent->p_left == current)
            parent->p_left = child;
        else
            parent->p_right = child;
        delete current;
        return;
    }

    // Case 2: has 2 child
    // Find successor (or predecessor)
    BST::BSTNode* successor = current->p_right;
    BST::BSTNode* successor_parent = current;
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
/// @return BSTNode*: root of created BST
void BST::createTree(int a[], int n) {
    if (n == 0) return;
    pRoot = createNode(a[0]);
    for (int i = 1; i < n; i++) { Insert(a[i]); }
}

/// @brief Remove all nodes of the tree, set the root node to nullptr
void BST::removeTree() {
    if (pRoot == nullptr) return;

    BSTNode* current = pRoot;
    Queue<BSTNode*> q;
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        q.pop();

        if (current->p_left != nullptr) q.push(current->p_left);
        if (current->p_right != nullptr) q.push(current->p_right);
        delete current;
    }

    pRoot = nullptr;

    return;
}

/// @brief Calculate height
/// @return height of the tree, also the depth of the deepest node
int BST::Height() {
    if (pRoot == nullptr) return 0;

    Queue<BST::BSTNode*> q;
    BST::BSTNode* current = pRoot;
    q.push(current);
    int height = 0;
    while (!q.empty()) {
        Queue<BST::BSTNode*> temp;
        while (!q.empty()) {
            BST::BSTNode* current = q.front();
            q.pop();
            if (current->p_left != nullptr) temp.push(current->p_left);
            if (current->p_right != nullptr) temp.push(current->p_right);
        }
        q = temp;
        height++;
    }
    return height;
}

/// @brief Count node of the tree
/// @return The number of nodes of the tree
int BST::countNode() {
    if (pRoot == nullptr) return 0;
    Queue<BSTNode*> q;
    q.push(pRoot);
    int count = 0;
    BSTNode* current;
    while (!q.empty()) {
        current = q.front();
        q.pop();
        count++;
        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }

    return count;
}

/// @brief Calculate sum of keys of nodes in the tree
/// @return sum of keys
int BST::sumNode() {
    if (pRoot == nullptr) return 0;
    Queue<BSTNode*> q;
    q.push(pRoot);
    int sum = 0;
    BSTNode* current;
    while (!q.empty()) {
        current = q.front();
        q.pop();
        sum += current->key;
        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }

    return sum;
}

/// @brief Find height of the node has key `value` in the tree
/// @param value
/// @return int: height of the node
int BST::heightNode(int value) {
    BSTNode* current = Search(value);
    if (current == nullptr) return -1;

    Queue<BSTNode*> q;
    q.push(current);
    // calculate height of tree from current, also the depth of the deepest node
    int height = 0;
    while (!q.empty()) {
        Queue<BSTNode*> temp;
        while (!q.empty()) {
            BSTNode* current = q.front();
            q.pop();
            if (current->p_left != nullptr) temp.push(current->p_left);
            if (current->p_right != nullptr) temp.push(current->p_right);
        }
        q = temp;
        height++;
    }
    return height;
}

// actually "depth" of node in ANY BINARY TREE
/// @brief Return level of the node in the tree
/// @param p (BSTNode*) the node that need to find level
/// @return int: level of the node
int BST::Level(BSTNode* p) {
    if (p == nullptr) return -1;
    BSTNode* current = pRoot;
    int level = 0;
    while (current != nullptr) {
        if (current == p) return level;
        level++;
        if (current->key < p->key)
            current = current->p_right;
        else
            current = current->p_left;
    }

    return -1;
}

/// @brief Count the number of leaf nodes in the tree
/// @return int: the number of leaf nodes
int BST::countLeaf() {
    if (pRoot == nullptr) return 0;

    BSTNode* current = pRoot;
    Queue<BSTNode*> q;
    q.push(current);
    int count = 0;
    while (!q.empty()) {
        current = q.front();
        q.pop();
        if (current->p_left == nullptr && current->p_right == nullptr) count++;
        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }
    return count;
}

/// @brief Count the number of nodes that its key less than x
/// @param x
/// @return int: the number of nodes that its key less than x
int BST::countLess(int x) {
    if (pRoot == nullptr) return 0;

    int count = 0;
    BSTNode* current = pRoot;
    Queue<BSTNode*> q;
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        q.pop();
        if (current->key < x) count++;
        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }
    return count;
}

/// @brief Count the number of nodes that its key greater than x
/// @param x
/// @return int: the number of nodes that its key less than x
int BST::countGreater(int x) {
    if (pRoot == nullptr) return 0;

    int count = 0;
    BSTNode* current = pRoot;
    Queue<BSTNode*> q;
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        q.pop();
        if (current->key > x) count++;
        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }
    return count;
}

/// @brief Check if a tree is a BST or not
/// @return true if that tree is BST, false otherwise
bool BST::isBST() {
    if (pRoot == nullptr) return true;
    Queue<dataCheck> q;
    BSTNode* current = pRoot;
    int min = -(1 << 30);
    int max = (1 << 30);
    q.push({current, min, max});
    while (!q.empty()) {
        current = q.front().pRoot;
        min = q.front().min;
        max = q.front().max;
        q.pop();
        if (current->key > max || current->key < min) return false;
        if (current->p_left) { q.push({current->p_left, min, current->key}); }
        if (current->p_right) { q.push({current->p_right, current->key, max}); }
    }

    return true;
}

/// @brief Check if a tree is full binary tree
/// @return true if that tree is a FBT, false otherwise
bool BST::isFullBinaryTree() {
    if (pRoot == nullptr) return true;
    Queue<BSTNode*> q;
    q.push(pRoot);
    BSTNode* current;
    while (!q.empty()) {
        current = q.front();
        q.pop();
        if (current->p_left == nullptr && current->p_right == nullptr) continue;
        if (current->p_left == nullptr || current->p_right == nullptr)
            return false;
        q.push(current->p_left);
        q.push(current->p_right);
    }

    return true;
}

/// @brief Check if a tree is a full BST
/// @return true if that tree is a full BST, false otherwise
bool BST::isFullBST() {
    return isBST() && isFullBinaryTree();
}

/// @brief Copy a tree to another tree
/// @param tree (BST) the tree need to be copied
void BST::copy(BST tree) {
    if (tree.pRoot == nullptr) return;

    removeTree();

    Queue<BSTNode*> q;
    q.push(tree.pRoot);
    BSTNode* current;
    while (!q.empty()) {
        current = q.front();
        q.pop();
        Insert(current->key);
        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }
    return;
}