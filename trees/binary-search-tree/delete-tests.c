#include <stdio.h>
#include <assert.h>
#include "../../_utils_/asserts.h"
#include "./binary-search-tree.h"

int main() {

    { // should delete when is root
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 1);
        bst_delete(tree, 1);
        assert(tree->root == NULL);
    }

    { // should delete when is left leaf
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 2);
        bst_insert(tree, 1);
        bst_delete(tree, 1);
        assert(tree->root->value == 2);
        assert(tree->root->left == NULL);
    }

    { // should delete when is right leaf
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 2);
        bst_insert(tree, 1);
        bst_insert(tree, 3);
        bst_delete(tree, 3);
        assert(tree->root->value == 2);
        assert(tree->root->left->value == 1);
        assert(tree->root->right == NULL);
    }

    { // should delete when is left deep leaf
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 2);
        bst_insert(tree, 1);
        bst_insert(tree, 0);
        bst_delete(tree, 0);
        assert(tree->root->value == 2);
        assert(tree->root->left->value == 1);
        assert(tree->root->left->left == NULL);
    }

    { // should delete when node has only the left child
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 4);
        bst_insert(tree, 2);
        bst_delete(tree, 4);
        assert(tree->root->value == 5);
        assert(tree->root->left->value == 2);
        assert(tree->root->left->right == NULL);
        assert(tree->root->left->left == NULL);
    }

    { // should delete when node has only the right child
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 6);
        bst_insert(tree, 7);
        bst_delete(tree, 6);
        assert(tree->root->value == 5);
        assert(tree->root->right->value == 7);
        assert(tree->root->right->right == NULL);
        assert(tree->root->right->left == NULL);
    }

    { // should delete when node has both left and right children
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 8);
        bst_insert(tree, 6);
        bst_insert(tree, 9);
        bst_delete(tree, 8);
        assert(tree->root->value == 5);
        assert(tree->root->right->value == 6);
        assert(tree->root->right->right->value == 9);
        assert(tree->root->right->left == NULL);
    }

    { // should delete when node has both left and right children (largest element)
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert_many(tree, (int[]){10,5,20,4,7,6,8,9}, 8);
        bst_delete(tree, 10);
        assert(tree->root->value == 9);
        assert(tree->root->right->value == 20);
        assert(tree->root->left->value == 5);
        assert(tree->root->left->left->value == 4);
        assert(tree->root->left->right->value == 7);
        assert(tree->root->left->right->left->value == 6);
        assert(tree->root->left->right->right->value == 8);
        assert(tree->root->left->right->right->right == NULL);
    }

    return 0;
}