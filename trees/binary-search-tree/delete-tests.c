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
        bst_insert_many(tree, (int[]){5,8,6,9}, 4);
        int expected[] = {5,6,8,9};
        assert_array(bst_inorder(tree), expected, 4);
        bst_delete(tree, 8);
        assert(tree->root->value == 5);
        assert(tree->root->right->value == 9);
        assert(tree->root->right->left->value == 6);
        assert(tree->root->right->right == NULL);
    }

    { // should delete when node has both left and right children (largest element without children)
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert_many(tree, (int[]){10,5,20,4,7,6,8,9}, 8);
        int expected[] = {4,5,6,7,8,9,10,20};
        assert_array(bst_inorder(tree), expected, 8);
        bst_delete(tree, 10);
        assert(tree->root->value == 20);
        assert(tree->root->right == NULL);
        assert(tree->root->left->value == 5);
        assert(tree->root->left->left->value == 4);
        assert(tree->root->left->right->value == 7);
        assert(tree->root->left->right->left->value == 6);
        assert(tree->root->left->right->right->value == 8);
        assert(tree->root->left->right->right->right->value == 9);
    }

    { // should delete when node has both left and right children (min element with child)
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert_many(tree, (int[]){10,5,13,20,15,14}, 6);
        bst_delete(tree, 10);
        assert(tree->root->value == 13);
        assert(tree->root->left->value == 5);
        assert(tree->root->right->value == 20);
        assert(tree->root->right->right == NULL);
        assert(tree->root->right->left->value == 15);
        assert(tree->root->right->left->left->value == 14);
        assert(tree->root->right->left->left->left == NULL);
    }

    { // should delete node on right side with one child
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert_many(tree, (int[]){1,2,3,4}, 4);
        bst_delete(tree, 2);

        assert(tree->root->value == 1);
        assert(tree->root->right->value == 3);
        assert(tree->root->right->right->value == 4);
        assert(tree->root->right->right->right == NULL);
    }

    { // should delete node on left side with two children 
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert_many(tree, (int[]){4,2,3,1}, 4);
        bst_delete(tree, 2);

        assert(tree->root->value == 4);
        assert(tree->root->left->value == 3);
        assert(tree->root->left->left->value == 1);
        assert(tree->root->left->right == NULL);
    }

    { // should delete node on right side with two children
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert_many(tree, (int[]){4,9,8,10,12,11}, 6);
        bst_delete(tree, 9);

        assert(tree->root->value == 4);
        assert(tree->root->right->value == 10);
        assert(tree->root->right->left->value == 8);
        assert(tree->root->right->right->value == 12);
        assert(tree->root->right->right->left->value == 11);
        assert(tree->root->right->right->right == NULL);
    }



    return 0;
}