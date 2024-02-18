#pragma once
#include <iostream>
#include <queue>

using namespace std;

// TreeNode struct representing each node in the binary search tree
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : key(value), left(nullptr), right(nullptr) {}
};

// BinarySearchTree class to handle operations on the binary search tree
class BinarySearchTree {
private:
    TreeNode* root;

    // Helper function for inserting a key into the binary search tree recursively
    TreeNode* insertRecursive(TreeNode* root, int key);

    // Helper function for performing inorder traversal recursively
    void inorderRecursive(TreeNode* root);
    void deleteNodes(TreeNode* root);

public:
    BinarySearchTree();
    BinarySearchTree(TreeNode* root);
    ~BinarySearchTree();

    // Public function to insert a key into the binary search tree
    void insert(int key);

    // Public function to perform inorder traversal of the binary search tree
    void inorderTraversal();
    void levelTraversal();
    int weightedSum(std::vector<int> weights);
};