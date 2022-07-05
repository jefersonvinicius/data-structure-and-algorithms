#include <stdio.h>
#include <assert.h>
#include "tree.h"

int main() {

    { // should create binary indexed tree
        struct BITree* tree = create_binary_indexed_tree();
        assert(tree != NULL);
        assert(tree->values != NULL);
    }

    { // should insert first value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        assert(tree->values[0] == 0);
        assert(tree->values[1] == 1);
        assert(tree->size == 2);
        assert(tree->original[0] == 0);
        assert(tree->original[1] == 1);
    }

    { // should insert second value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        bi_insert(tree, 2);
        assert(tree->values[0] == 0);
        assert(tree->values[1] == 1);
        assert(tree->values[2] == 3);
        assert(tree->size == 3);
        assert(tree->original[0] == 0);
        assert(tree->original[1] == 1);
        assert(tree->original[2] == 2);
    }

    { // should insert third value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        bi_insert(tree, 2);
        bi_insert(tree, 3);
        assert(tree->values[0] == 0);
        assert(tree->values[1] == 1);
        assert(tree->values[2] == 3);
        assert(tree->values[3] == 3);
        assert(tree->size == 4);
        assert(tree->original[0] == 0);
        assert(tree->original[1] == 1);
        assert(tree->original[2] == 2);
        assert(tree->original[3] == 3);
    }

    { // should insert fourth value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        bi_insert(tree, 2);
        bi_insert(tree, 3);
        bi_insert(tree, 4);
        assert(tree->values[0] == 0);
        assert(tree->values[1] == 1);
        assert(tree->values[2] == 3);
        assert(tree->values[3] == 3);
        assert(tree->values[4] == 10);
        assert(tree->size == 5);
        assert(tree->original[0] == 0);
        assert(tree->original[1] == 1);
        assert(tree->original[2] == 2);
        assert(tree->original[3] == 3);
        assert(tree->original[4] == 4);
    }



    { // should get sum until index 5
        // struct BITree* tree = create_binary_indexed_tree();
        // for (int i = 1; i <= 8; i++) bi_insert(tree, i);
        // bi_print(tree);
        // assert(bi_get_sum(tree, 5) == 15);
    }


    return 0;
}