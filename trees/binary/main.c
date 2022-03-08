#include <stdio.h>
#include <assert.h>

#include "tree.h"

int main() {

    { // create node correctly
        struct Node* node = create_node(2);
        assert(node->value == 2);
        assert(node->left == NULL);
        assert(node->right == NULL);
    }

    { // create tree correctly
        struct Tree* tree = create_binary_tree();
        assert(tree->root == NULL);
    }

    { // attach child correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(0);
        tree->root->right = create_node(1);
        tree->root->left = create_node(2);
        assert(tree->root->value == 0);
        assert(tree->root->right->value == 1);
        assert(tree->root->left->value == 2);
    }

    return 0;
}