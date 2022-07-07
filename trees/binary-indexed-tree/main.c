#include <stdio.h>
#include <assert.h>
#include "tree.h"
#include "../../_utils_/asserts.h"

int main() {

    { // should create binary indexed tree
        struct BITree* tree = create_binary_indexed_tree();
        assert(tree != NULL);
        assert(tree->indexed != NULL);
    }

    { // should insert first value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        assert(tree->indexed[0] == 0);
        assert(tree->indexed[1] == 1);
        assert(tree->size == 2);
        assert(tree->raw[0] == 0);
        assert(tree->raw[1] == 1);
    }

    { // should insert second value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        bi_insert(tree, 2);
        assert(tree->indexed[0] == 0);
        assert(tree->indexed[1] == 1);
        assert(tree->indexed[2] == 3);
        assert(tree->size == 3);
        assert(tree->raw[0] == 0);
        assert(tree->raw[1] == 1);
        assert(tree->raw[2] == 2);
    }

    { // should insert third value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        bi_insert(tree, 2);
        bi_insert(tree, 3);
        assert(tree->indexed[0] == 0);
        assert(tree->indexed[1] == 1);
        assert(tree->indexed[2] == 3);
        assert(tree->indexed[3] == 3);
        assert(tree->size == 4);
        assert(tree->raw[0] == 0);
        assert(tree->raw[1] == 1);
        assert(tree->raw[2] == 2);
        assert(tree->raw[3] == 3);
    }

    { // should insert fourth value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 1);
        bi_insert(tree, 2);
        bi_insert(tree, 3);
        bi_insert(tree, 4);
        assert(tree->indexed[0] == 0);
        assert(tree->indexed[1] == 1);
        assert(tree->indexed[2] == 3);
        assert(tree->indexed[3] == 3);
        assert(tree->indexed[4] == 10);
        assert(tree->size == 5);
        assert(tree->raw[0] == 0);
        assert(tree->raw[1] == 1);
        assert(tree->raw[2] == 2);
        assert(tree->raw[3] == 3);
        assert(tree->raw[4] == 4);
    }

    { // should insert many
        struct BITree* tree = create_binary_indexed_tree(); 
        int array[] = {0,5,2,9,-3,5,20,10,-7,2,3,-4,0,-2,15,5};
        int indexed[] = {0,5,7,9,13,5,25,10,41,2,5,-4,1,-2,13,5}; 
        int size = sizeof(int) / sizeof(indexed);
        for (int i = 1; i < 16; i++) bi_insert(tree, array[i]);

        assert_array(tree->raw, array, 16);
        assert_array(tree->indexed, indexed, 16);
    }


    { // should get sum until index 0 (inclusive)
        struct BITree* tree = create_binary_indexed_tree();
        for (int i = 1; i <= 8; i++) bi_insert(tree, i);
        bi_print(tree);
        assert(bi_get_sum(tree, 0) == 1);
    }


    { // should get sum until index 5 (inclusive)
        struct BITree* tree = create_binary_indexed_tree();
        for (int i = 1; i <= 8; i++) bi_insert(tree, i);
        assert(bi_get_sum(tree, 5) == 21);
    }


    return 0;
}