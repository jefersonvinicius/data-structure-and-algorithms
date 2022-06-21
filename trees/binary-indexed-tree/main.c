#include <stdio.h>
#include <assert.h>
#include "tree.h"

int main() {

    { // should create binary indexed tree
        struct BITree* tree = create_binary_indexed_tree();
        assert(tree != NULL);
        assert(tree->root == NULL);
    }

    { // should insert node
        struct BITree* tree = create_binary_indexed_tree();
    }

    return 0;
}