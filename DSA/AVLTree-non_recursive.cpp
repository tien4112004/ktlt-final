#include "AVLTree.h"

/// @brief Find height of a node in tree
/// @return (int) height of pRoot
int AVL::AVLNode::getHeight() {
    if (this == nullptr) return 0;
    return height;
}

/// @brief Set height of the node
/// @param h (int) the height to be set
void AVL::AVLNode::setHeight(int h) {
    if (this == nullptr) return;
    height = h;
}

/// @brief Find balance factor (difference between height(left) and
/// height(right)) of node.
/// @return (int) balance factor of node
int AVL::AVLNode::getBalanceFactor() {
    if (this == nullptr) return (1 << 30);
    int rightHeight = (p_right != nullptr) ? p_right->getHeight() : 0;
    int leftHeight = (p_left != nullptr) ? p_left->getHeight() : 0;
    return rightHeight - leftHeight;
}

/// @brief left rotate node x
AVL::AVLNode* AVL::AVLNode::rotateLeft() {
    if (this == nullptr) return nullptr;
    // std::cout << "\n[rotate left] " << x->key << '\n';
    // change the connections between nodes
    AVLNode* y = this->p_right;
    this->p_right = y->p_left;
    y->p_left = this;
    // update x height
    int rightHeight = (p_right != nullptr) ? p_right->getHeight() : 0;
    int leftHeight = (p_left != nullptr) ? p_left->getHeight() : 0;
    this->setHeight(std::max(rightHeight, leftHeight) + 1);
    // update y height
    rightHeight = (y->p_right != nullptr) ? y->p_right->getHeight() : 0;
    leftHeight = (y->p_left != nullptr) ? y->p_left->getHeight() : 0;
    y->setHeight(std::max(rightHeight, leftHeight) + 1);
    return y;
}

/// @brief right rotate node x
AVL::AVLNode* AVL::AVLNode::rotateRight() {
    if (this == nullptr) return nullptr;
    // std::cout << "\n[rotate right] " << x->key << '\n';
    AVLNode* y = this->p_left;
    this->p_left = y->p_right;
    y->p_right = this;
    // update x height
    int rightHeight = (p_right != nullptr) ? p_right->getHeight() : 0;
    int leftHeight = (p_left != nullptr) ? p_left->getHeight() : 0;
    this->setHeight(std::max(rightHeight, leftHeight) + 1);
    // update y height
    rightHeight = (y->p_right != nullptr) ? y->p_right->getHeight() : 0;
    leftHeight = (y->p_left != nullptr) ? y->p_left->getHeight() : 0;
    y->setHeight(std::max(rightHeight, leftHeight) + 1);
    return y;
}

/// @brief Create new node with key = data
/// @param data (int) the key to be inserted
/// @return AVLNode*: the created node
AVL::AVLNode* AVL::createNode(int data) {
    AVLNode* new_node;
    try {
        new_node = new AVLNode{data, nullptr, nullptr, 1};
    }
    catch (...) {
        throw std::runtime_error("Cannot allocate memory! No node created.");
    }

    return new_node;
}

int height(AVL::AVLNode* pRoot) {
    if (pRoot == nullptr) return 0;
    return pRoot->getHeight();
}

int getBalanceFactor(AVL::AVLNode* pRoot) {
    if (pRoot == nullptr) return (1 << 30);
    return pRoot->getBalanceFactor();
}

/// @brief Insert node with UNIQUE key x into pRoot
/// @param x (int) the key to be inserted
void AVL::Insert(int x) {
    Stack<AVLNode**> ancestors;
    AVLNode** ppNode = &pRoot;

    while (*ppNode) {
        ancestors.push(ppNode);
        if (x < (*ppNode)->key) { ppNode = &(*ppNode)->p_left; }
        else if (x > (*ppNode)->key) { ppNode = &(*ppNode)->p_right; }
        else {
            return; // value duplicated, not add to tree
        }
    }

    *ppNode = createNode(x);
    while (!ancestors.empty()) {
        ppNode = ancestors.front();
        ancestors.pop();

        (*ppNode)->setHeight(
            1
            + std::max(height((*ppNode)->p_left), height((*ppNode)->p_right)));
        int balanceFactor = getBalanceFactor(*ppNode);

        if (balanceFactor < -1) {
            if (x < (*ppNode)->p_left->key) {
                *ppNode = (*ppNode)->rotateRight();
            }
            else if (x > (*ppNode)->p_left->key) {
                (*ppNode)->p_left = (*ppNode)->p_left->rotateLeft();
                *ppNode = (*ppNode)->rotateRight();
            }
        }
        else if (balanceFactor > 1) {
            if (x > (*ppNode)->p_right->key) {
                *ppNode = (*ppNode)->rotateLeft();
            }
            else if (x < (*ppNode)->p_right->key) {
                (*ppNode)->p_right = (*ppNode)->p_right->rotateRight();
                *ppNode = (*ppNode)->rotateLeft();
            }
        }
    }
}

/// @brief Remove node has key x from the tree
/// @param x (int) the key to be deleted
void AVL::Remove(int x) {
    AVLNode** ppNode = &pRoot;
    Stack<AVLNode**> ancestors;
    while (*ppNode != nullptr) {
        ancestors.push(ppNode);
        if (x < (*ppNode)->key) { ppNode = &(*ppNode)->p_left; }
        else if (x > (*ppNode)->key) { ppNode = &(*ppNode)->p_right; }
        else {
            if ((*ppNode)->p_left == nullptr || (*ppNode)->p_right == nullptr) {
                AVLNode* temp = ((*ppNode)->p_left ? (*ppNode)->p_left
                                                   : (*ppNode)->p_right);
                if (temp == nullptr) {
                    // std::cout << "[Log] Case 0 - Removed " << (*ppNode)->key
                    //           << ".\n";
                    temp = *ppNode;
                    *ppNode = nullptr;
                    temp->setHeight(1);
                    ancestors.pop();
                } // pRoot is leaf node
                else {
                    // std::cout << "[Log] Case 1 - Removed " << (*ppNode)->key
                    //           << ".\n";
                    **ppNode = *temp;
                }
                delete temp;
            }
            else {
                AVLNode* successor = (*ppNode)->p_right;
                ancestors.push(&successor);
                while (successor->p_left != nullptr) {
                    ancestors.push(&successor);
                    successor = successor->p_left;
                }
                (*ppNode)->key = successor->key;
                ancestors.pop();
                AVLNode* successor_parent;
                // if (!ancestors.empty()) {
                successor_parent = *(ancestors.front());
                if (successor->p_right != nullptr)
                    ancestors.push(&successor->p_right);
                if (successor_parent->p_left == successor)
                    successor_parent->p_left = successor->p_right;
                else
                    successor_parent->p_right = successor->p_right;
                delete successor;
            }
            break;
        }
    }
    while (!ancestors.empty()) {
        ppNode = ancestors.front();
        ancestors.pop();
        (*ppNode)->setHeight(
            1
            + std::max(height((*ppNode)->p_left), height((*ppNode)->p_right)));
        int balanceFactor = getBalanceFactor(*ppNode);
        if (balanceFactor < -1) {
            if ((*ppNode)->p_left->getBalanceFactor() <= 0) {
                *ppNode = (*ppNode)->rotateRight();
            } // left-left case
            else {
                (*ppNode)->p_left = (*ppNode)->p_left->rotateLeft();
                *ppNode = (*ppNode)->rotateRight();
            } // left-right case
        }
        if (balanceFactor > 1) {
            if ((*ppNode)->p_right->getBalanceFactor() >= 0) {
                *ppNode = (*ppNode)->rotateLeft();
            } // right-right case
            else {
                (*ppNode)->p_right = (*ppNode)->p_right->rotateRight();
                *ppNode = (*ppNode)->rotateLeft();
            } // right-left case
        }
    }
}

/// @brief Preorder traversal
void AVL::NLR() {
    if (pRoot == nullptr) return;

    Stack<AVLNode*> s;
    s.push(pRoot);
    AVLNode* current = pRoot;
    while (!s.empty()) {
        current = s.front();
        s.pop();
        std::cout << current->key << ' ';
        if (current->p_left) s.push(current->p_left);
        if (current->p_right) s.push(current->p_right);
    }
    return;
}

/// @brief Inorder traversal
void AVL::LNR() {
    if (pRoot == nullptr) return;
    Stack<AVL::AVLNode*> s;
    AVL::AVLNode* current = pRoot;
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->p_left;
        }
        current = s.front();
        std::cout << current->key << ' ';
        current = current->p_right;
        s.pop();
    }
    return;
}

/// @brief Postorder traversal
void AVL::LRN() {
    if (pRoot == nullptr) return;

    Stack<AVL::AVLNode*> s;
    AVL::AVLNode* current = pRoot;
    AVL::AVLNode* last_visited = nullptr;

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
        else { current = current->p_right; }
    }
    return;
}

/// @brief Level order traversal, using BFS
void AVL::LevelOrder() {
    if (pRoot == nullptr) return;

    Queue<AVLNode*> q;
    AVLNode* current = pRoot;
    q.push(current);
    int level = 0;
    while (!q.empty()) {
        Queue<AVLNode*> temp;
        std::cout << level << ": ";
        while (!q.empty()) {
            AVLNode* current = q.front();
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
/// @return true if pRoot is a valid AVL tree, false otherwise.
bool AVL::isAVL() {
    if (pRoot == nullptr) return true;
    Queue<dataCheck> q;
    q.push({pRoot, -(1 << 30), (1 << 30)});
    while (!q.empty()) {
        dataCheck current = q.front();
        q.pop();
        if (current.pRoot->key < current.min || current.pRoot->key > current.max
            || getBalanceFactor(current.pRoot) > 1
            || getBalanceFactor(current.pRoot) < -1)
            return false;
        if (current.pRoot->p_left != nullptr)
            q.push({current.pRoot->p_left, current.min, current.pRoot->key});
        if (current.pRoot->p_right != nullptr)
            q.push({current.pRoot->p_right, current.pRoot->key, current.max});
    }
    return true;
}

/// @brief Print the tree from root
/// @param pRoot (AVLNode*) the root of the tree
/// @param indent (std::string)
/// @param last (bool) true
void AVL::printTree(AVLNode* pRoot, std::string indent, bool last) {
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

/// @brief Copy a tree to another tree
/// @param tree (AVL) the tree need to be copied
void AVL::copy(AVL tree) {
    if (tree.pRoot == nullptr) return;

    AVLNode* current = pRoot;
    Queue<AVLNode*> q;
    if (current != nullptr) q.push(current);

    // removeTree
    while (!q.empty()) {
        current = q.front();
        q.pop();

        if (current->p_left != nullptr) q.push(current->p_left);
        if (current->p_right != nullptr) q.push(current->p_right);
        delete current;
    }

    q.push(tree.pRoot);
    while (!q.empty()) {
        current = q.front();
        q.pop();
        Insert(current->key);
        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }
    return;
}