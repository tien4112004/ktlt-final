#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int data) {
    // struct Node *node = (struct Node*)malloc(sizeof(struct Node)); // c-style
    Node* node = new Node;

    node->key = data;
    node->left = node->right = NULL;
    return node;
}

void inorderTraversal(struct Node* root) {
    if (root == NULL) return;

    inorderTraversal(root->left);
    cout << root->key << ' ';
    inorderTraversal(root->right);
}

void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    cout << root->key << ' ';
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postOrderTraversal(struct Node* root) {
    if (root == NULL) return;

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->key << ' ';
}

struct Node* insertNode(struct Node* node, int key) {
    // Return a new node if the tree is empty
    if (node == NULL) return newNode(key);

    // Traverse to the right place and insert the node
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else
        node->right = insertNode(node->right, key);

    return node;
}

// Find the inorder successor
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    // Find the leftmost leaf
    while (current && current->left != NULL) current = current->left;

    return current;
}

// Deleting a node
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // If the node is with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            delete root;
            return temp;
        }

        // If the node has 2 childrens
        // Find the successor
        struct Node* temp = minValueNode(root->right);

        // Place the inorder successor in position of the node to be deleted
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    struct Node* root = NULL;
    root = insertNode(root, 33);
    root = insertNode(root, 4);
    root = insertNode(root, 12);
    root = insertNode(root, 8);
    root = insertNode(root, 10);
    root = insertNode(root, 26);
    root = insertNode(root, 20);
    root = insertNode(root, 16);
    root = insertNode(root, 43);
    root = insertNode(root, 41);
    root = insertNode(root, 74);
    root = insertNode(root, 77);
    root = insertNode(root, 55);
    root = insertNode(root, 52);
    root = insertNode(root, 64);

    cout << "Preorder traversal: ";
    preorderTraversal(root);
    cout << '\n';
    cout << "PostOrder traversal: ";
    postOrderTraversal(root);

    cout << "\nAfter deleting 6\n";
    root = deleteNode(root, 6);
    cout << "Inorder traversal: ";
    inorderTraversal(root);

    // cout << "\nTime: " << clock() / (double)1000 << " secs"; // CLOCK
    return 0;
}