#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

struct BSTree {
    Node* root;
};

void initialize(BSTree** tree) {
    *tree = new BSTree;
    (*tree)->root = NULL;
}

Node* createNode(int data) {
    Node* new_node;
    try {
        new_node = new Node;
    }
    catch (...) {
        std::cout << "Cannot create new node.\n";
        return nullptr;
    }
    new_node->key = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void insertNode(BSTree* tree, int key) {
    if (tree == nullptr) { return; }
    Node* new_node = createNode(key);

    Node* node = tree->root;
    if (node == nullptr) {
        tree->root = new_node;
        return;
    }

    Node* current = node;
    Node* prev;
    while (current != nullptr) {
        prev = current;
        if (key < current->key) { current = current->left; }
        else { current = current->right; }
    }
    if (prev->key > key) { prev->left = new_node; }
    else { prev->right = new_node; }
    return;
}

// Successor has to be the largest node in the left subtree or the smallest node
// in the right subtree
void deleteNode(BSTree* tree, int key) {
    if (tree == nullptr) { return; }

    Node* parent = tree->root;
    Node* current = tree->root;
    // memset()
    // find the node to be deleted
    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) { current = current->left; }
        else { current = current->right; }
    }

    if (current == nullptr) {
        parent = tree->root;
        current = tree->root;
    }

    // case 1: to_be_deleted is leaf node;
    if (current->left == nullptr && current->right == nullptr) {
        if (parent->left == current) { parent->left = nullptr; }
        else { parent->right = nullptr; }
        delete current;
        return;
    }

    // case 2: to_be_deleted has only 1 child
    if (current->left == nullptr || current->right == nullptr) {
        Node* child = current->left == nullptr ? current->right : current->left;
        if (parent->left == current) { parent->left = child; }
        else { parent->right = child; }
        delete current;
        return;
    }

    // case 3: to_be_deleted has 2 child
    // find the successor
    Node* successor = current->right;
    Node* successor_parent = current;
    while (successor->left != nullptr) {
        successor_parent = successor;
        successor = successor->left;
    }
    // successor is the right child of current
    if (successor_parent->left == successor) {
        successor_parent->left = successor->right;
    }
    else { successor_parent->right = successor->right; }
    current->key = successor->key;
    delete successor;
    return;
}

Node* search(const BSTree* tree, int value) {
    if (tree == nullptr) { return nullptr; }

    Node* current = tree->root;
    while (current != nullptr) {
        if (value < current->key) { current = current->left; }
        else { current = current->right; }

        if (current->key == value) { return current; }
    }
    std::cout << "Not found.\n";
    return nullptr;
}

// preorder traversal: current -> left -> right
void preTravel(const BSTree* tree) {
    if (tree == nullptr) { return; }

    stack<Node*> s;
    Node* current = tree->root;
    s.push(current);
    while (!s.empty()) {
        std::cout << s.top()->key << ' ';
        current = s.top();
        s.pop();
        if (current->right != nullptr) s.push(current->right);
        if (current->left != nullptr) s.push(current->left);
    }

    return;
}

// Inorder_traversal: left->current->right, this will give us a sorted array
void inTravel(BSTree* tree) {
    if (tree == nullptr || tree->root == nullptr) { return; }

    // approach #1: Morris traversal
    // Node* current = tree->root;
    // while (current != nullptr) {
    //     if (current->left == nullptr) {
    //         std::cout << current->key << ' ';
    //         current = current->right;
    //         continue;
    //     }

    //     Node* pre = current->left;
    //     while (pre->right != nullptr && pre->right != current) {
    //         pre = pre->right;
    //     }
    //     if (pre->right == nullptr) {
    //         pre->right = current;
    //         current = current->left;
    //     }
    //     else {
    //         pre->right = nullptr;
    //         std::cout << current->key << ' ';
    //         current = current->right;
    //     }
    // }

    // approach #2: stack
    /*
    1. Create an empty stack (say S).
    2. Initialize the current node as root.
    3. Push the current node to S and set current = current->left until current
    is NULL
    4. If current is NULL and the stack is not empty then:
            Pop the top item from the stack.
            Print the popped item and set current = popped_item->right
            Go to step 3.
    5. If current is NULL and the stack is empty then we are done.
    */
    stack<Node*> s;
    // s.push(tree->root);
    Node* current = tree->root;
    while (true) {
        if (current != nullptr) {
            s.push(current);
            current = current->left;
            continue;
        }

        if (s.empty()) { break; }

        current = s.top();
        s.pop();
        std::cout << current->key << ' ';
        current = current->right;
    }
    return;

    // approach #3: recursion
    // void preTravel(Node* node) {
    // preTravel(tree->root->left);
    // std::cout << tree->root->key << ' ';
    // preTravel(tree->root->right);
    // }
}

// postTraversal: left->right->current,
void postTravel(BSTree* tree) {
    if (tree == nullptr || tree->root == nullptr) { return; }

    stack<Node*> s;
    Node* current = tree->root;
    s.push(current);
    Node* prev = nullptr;
    while (!s.empty()) {
        current = s.top();
        if (prev == NULL || prev->left == current || prev->right == current) {
            if (current->left != nullptr) { s.push(current->left); }
            else if (current->right != nullptr) { s.push(current->right); }
            else {
                std::cout << current->key << ' ';
                s.pop();
            }
        }
        else if (current->left == prev) {
            if (current->right != nullptr) { s.push(current->right); }
            else {
                std::cout << current->key << ' ';
                s.pop();
            }
        }
        else if (current->right == prev) {
            std::cout << current->key << ' ';
            s.pop();
        }
        prev = current;
    }
}

void BFS(BSTree* tree) {
    if (tree == nullptr) { return; }
    queue<Node*> q;
    Node* current = tree->root;
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        std::cout << current->key << ' ';
        q.pop();
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    return;
}

void DFS(BSTree* tree) {
    if (tree == nullptr) { return; }
    stack<Node*> s;
    Node* current = tree->root;
    s.push(current);
    while (!s.empty()) {
        current = s.top();
        std::cout << current->key << ' ';
        s.pop();
        if (current->right != nullptr) s.push(current->right);
        if (current->left != nullptr) s.push(current->left);
    }
    return;
}

void deinitialize(BSTree* tree) {
    if (tree == nullptr) { return; }
    Node* current = tree->root;
    queue<Node*> q;
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        q.pop();
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
        delete current;
    }
    delete tree;
    return;
}

int main() {
    BSTree* tree;
    initialize(&tree);
    insertNode(tree, 5);
    insertNode(tree, 3);
    insertNode(tree, 7);
    insertNode(tree, 2);
    insertNode(tree, 4);
    insertNode(tree, 6);
    insertNode(tree, 8);
    insertNode(tree, 1);
    insertNode(tree, 9);
    insertNode(tree, 10);
    insertNode(tree, 11);

    // insertNode(tree, 1);
    // insertNode(tree, 20);
    // insertNode(tree, 19);
    // insertNode(tree, 18);
    // insertNode(tree, 3);
    // insertNode(tree, 2);
    // insertNode(tree, 17);

    deleteNode(tree, 5);
    inTravel(tree);
}