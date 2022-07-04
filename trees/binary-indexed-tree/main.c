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
        bi_insert(tree, 4);
        assert(tree->values[0] == 0);
        assert(tree->values[1] == 4);
    }

    { // should insert second value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 4);
        bi_insert(tree, 5);
        assert(tree->values[0] == 0);
        assert(tree->values[1] == 4);
        assert(tree->values[2] == 5);
    }

    { // should insert third value
        struct BITree* tree = create_binary_indexed_tree();
        bi_insert(tree, 4);
        bi_insert(tree, 5);
        bi_insert(tree, 10);
        assert(tree->values[0] == 0);
        assert(tree->values[1] == 4);
        assert(tree->values[2] == 15);
        assert(tree->values[3] == 10);
    }

    printf("Bla: ");
    for (int i = 1; i <= 10; i += i & -i) {
        printf("%d ", i);
    }
    printf("\n");


    { // should get sum until index 5
        struct BITree* tree = create_binary_indexed_tree();
        // [1,2,3,4,5,6,7,8]
        for (int i = 1; i <= 8; i++) bi_insert(tree, i);
        bi_print(tree);
        assert(bi_get_sum(tree, 5) == 15);
    }


    return 0;
}