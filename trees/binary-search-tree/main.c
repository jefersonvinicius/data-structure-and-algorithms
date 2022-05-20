#include <stdio.h>
#include <assert.h>
#include "./binary-search-tree.h"

int main() {

    { // should create binary search tree
        struct BinarySearchTree* tree = create_binary_search_tree();
        assert(tree->root == NULL);
    }

    { // should create node
        struct Node* node = create_node(2);
        assert(node->value == 2);
        assert(node->right == NULL); 
        assert(node->left == NULL); 
    }

    { // should insert node at root when binary tree is empty
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 1);
        assert(tree->root->value == 1);
        assert(tree->root->left == NULL);
        assert(tree->root->right == NULL);
    }

    return 0;
}