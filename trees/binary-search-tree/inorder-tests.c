#include <stdio.h>
#include <assert.h>
#include "../../_utils_/asserts.h"
#include "./binary-search-tree.h"

int main() {

    { // should get sorted array
        struct BinarySearchTree* tree = create_binary_search_tree();
        bst_insert(tree, 1);
        bst_insert(tree, 10);
        bst_insert(tree, -1);
        bst_insert(tree, 2);
        bst_insert(tree, 0);
        bst_insert(tree, 2);
        bst_insert(tree, 12);
        bst_insert(tree, 100);
        int* result = bst_inorder(tree);
        int expected[] = {-1, 0, 1, 2, 2, 10, 12, 100};
        assertArray(result, expected, 8);
    }

    return 0;
}