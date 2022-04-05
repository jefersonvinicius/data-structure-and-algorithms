#include <stdio.h>
#include <assert.h>
#include "../_utils_/asserts.h"

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

    { // should get size correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(0);
        tree->root->right = create_node(1);
        tree->root->left = create_node(2);
        tree->root->left->left = create_node(3);
        tree->root->left->right = create_node(10);
        tree->root->right->left = create_node(11);
        assert(tree_size(tree) == 6);
    }

    { // should get in order transversal correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(1);
        tree->root->left = create_node(2);
        tree->root->right = create_node(3);
        tree->root->left->left = create_node(4);
        tree->root->left->right = create_node(5);
        tree->root->right->left = create_node(6);

        int* result = in_order(tree);
        int expected[] = {4, 2, 5, 1, 6, 3};
        assertArray(result, expected, 6);
    }

    { // should get pre order transversal correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(1);
        tree->root->left = create_node(2);
        tree->root->right = create_node(3);
        tree->root->left->left = create_node(4);
        tree->root->left->right = create_node(5);
        tree->root->right->left = create_node(6);

        int* result = pre_order(tree);
        int expected[] = {1, 2, 4, 5, 3, 6};
        assertArray(result, expected, 6);
    }

    { // should get post order transversal correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(1);
        tree->root->left = create_node(2);
        tree->root->right = create_node(3);
        tree->root->left->left = create_node(4);
        tree->root->left->right = create_node(5);
        tree->root->right->left = create_node(6);

        int* result = post_order(tree);
        int expected[] = {4, 5, 2, 6, 3, 1};
        assertArray(result, expected, 6);
    }

    return 0;
}