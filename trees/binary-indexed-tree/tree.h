#include <stdlib.h>

#define MAX_BI_TREE_SIZE

struct BITree {
    int[MAX_BI_TREE_SIZE] values;
};

struct BITree* create_binary_indexed_tree() {
    struct BITree* tree = malloc(sizeof(struct BITree*));
    return tree;
}

void bi_insert(struct BITree* tree, int value) {

}