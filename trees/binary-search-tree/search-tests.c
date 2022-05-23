#include <stdio.h>
#include <assert.h>
#include "./binary-search-tree.h"

int main() {

    { // should return node when is in the root
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        struct Node* result = bst_search(tree, 5);
        assert(result->value == 5);
    }

    { // should return node when is in the left
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 4);
        struct Node* result = bst_search(tree, 4);
        assert(result->value == 4);
    }

    { // should return node when is in the right
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 4);
        bst_insert(tree, 8);
        struct Node* result = bst_search(tree, 8);
        assert(result->value == 8);
    }

    { // should return node when is in the left leaves
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 4);
        bst_insert(tree, 8);
        bst_insert(tree, 1);
        struct Node* result = bst_search(tree, 1);
        assert(result->value == 1);
    }

    { // should return node when is in the right leaves
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 4);
        bst_insert(tree, 8);
        bst_insert(tree, 9);
        struct Node* result = bst_search(tree, 9);
        assert(result->value == 9);
    }

    { // should return NULL when not found the node
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 4);
        bst_insert(tree, 8);
        bst_insert(tree, 9);
        struct Node* result = bst_search(tree, 10);
        assert(result == NULL);
    }

    return 0;
}