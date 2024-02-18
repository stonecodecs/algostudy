#include<iostream>
#include"bst.h"

using namespace std;

// Helper function for inserting a key into the binary search tree recursively
TreeNode* BinarySearchTree::insertRecursive(TreeNode* root, int key) {
    if (root == nullptr) {
        return new TreeNode(key);
    }
    if (key < root->key) {
        root->left = insertRecursive(root->left, key);
    } else if (key > root->key) {
        root->right = insertRecursive(root->right, key);
    }
    return root;
}

// Helper function for performing inorder traversal recursively
void BinarySearchTree::inorderRecursive(TreeNode* root) {
    if (root != nullptr) {
        inorderRecursive(root->left);
        cout << root->key << " ";
        inorderRecursive(root->right);
    }
}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::BinarySearchTree(TreeNode* _root) : root(_root) {}

void BinarySearchTree::deleteNodes(TreeNode* root) {
    if (root != nullptr) {
        deleteNodes(root->left);
        deleteNodes(root->right);
        delete root;
    }
}

BinarySearchTree::~BinarySearchTree() {
    deleteNodes(root);
}

// Public function to insert a key into the binary search tree
void BinarySearchTree::insert(int key) {
    root = insertRecursive(root, key);
}

// Public function to perform inorder traversal of the binary search tree
void BinarySearchTree::inorderTraversal() {
    inorderRecursive(root);
}

void BinarySearchTree::levelTraversal() {
    if (root == nullptr) {
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            std::cout << node->key << " "; // Print node value

            // Enqueue left and right children for the next level
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        std::cout << std::endl; // Move to the next line after printing all nodes at the current level
    }
}

int BinarySearchTree::weightedSum(std::vector<int> weights) {
    // same as level traversal
    int sum{0};
    int level{1};
    if (root == nullptr) {
        return sum;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            sum += weights[node->key] * level;

            // Enqueue left and right children for the next level
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        level++;
    }

    return sum;
}