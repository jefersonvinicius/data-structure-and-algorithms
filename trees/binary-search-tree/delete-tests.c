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


    return 0;
}