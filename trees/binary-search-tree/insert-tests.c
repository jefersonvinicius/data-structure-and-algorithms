#include <stdio.h>
#include <assert.h>
#include "../../_utils_/asserts.h"
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

    { // should insert node at left side when root is bigger
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 2);
        assert(tree->root->value == 5);
        assert(tree->root->left->value == 2);
        assert(tree->root->right == NULL);
    }

    { // should insert node at right side when root is lower
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 2);
        bst_insert(tree, 7);
        assert(tree->root->value == 5);
        assert(tree->root->left->value == 2);
        assert(tree->root->right->value == 7);
    }

    { // should insert node at right side of leave
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 2);
        bst_insert(tree, 7);
        bst_insert(tree, 3);
        assert(tree->root->value == 5);
        assert(tree->root->left->value == 2);
        assert(tree->root->right->value == 7);
        assert(tree->root->left->right->value == 3);
        assert(tree->root->left->left == NULL);
    }

    { // should insert node at left side of leave
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 2);
        bst_insert(tree, 7);
        bst_insert(tree, 1);
        assert(tree->root->value == 5);
        assert(tree->root->left->value == 2);
        assert(tree->root->right->value == 7);
        assert(tree->root->left->left->value == 1);
        assert(tree->root->left->right == NULL);
    }

    { // should insert node at right side of leaves tree
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 2);
        bst_insert(tree, 7);
        bst_insert(tree, 8);
        assert(tree->root->value == 5);
        assert(tree->root->left->value == 2);
        assert(tree->root->right->value == 7);
        assert(tree->root->right->right->value == 8);
        assert(tree->root->right->left == NULL);
    }

    { // should insert node at left side of leaves tree
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 5);
        bst_insert(tree, 2);
        bst_insert(tree, 7);
        bst_insert(tree, 6);
        assert(tree->root->value == 5);
        assert(tree->root->left->value == 2);
        assert(tree->root->right->value == 7);
        assert(tree->root->right->left->value == 6);
        assert(tree->root->right->right == NULL);
    }

    { // should insert many nodes
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert_many(tree, (int[]){10,5,20,4,6,7,8,9}, 8);
        assertArray(bst_inorder(tree), (int[]){4,5,6,7,8,9,10,20}, 8);
    }

    return 0;
}