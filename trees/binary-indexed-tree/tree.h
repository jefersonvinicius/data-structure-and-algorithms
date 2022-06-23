#include <stdlib.h>
#include <string.h>

#define MAX_BI_TREE_SIZE 10000

struct BITree {
    int* values;
    int size;
};

struct BITree* create_binary_indexed_tree() {
    struct BITree* tree = malloc(sizeof(struct BITree*));
    tree->values = malloc(sizeof(int) * MAX_BI_TREE_SIZE);
    tree->size = 0;
    return tree;
};

void bi_insert(struct BITree* tree, int value) {
    int index = tree->size + 1, n = tree->size + 1;
    while (index <= n) {
        tree->values[index] += value;
        index += index & (-index);
    }
    tree->size++;
}

int bi_get_sum(struct BITree* tree, int end) {
    int sum = 0, index = end + 1;
    while (index > 0) {
        printf("index: %d\n", index);
        sum += tree->values[index];
        index -= index & (-index);
    }
    return sum;
}

int bi_print(struct BITree* tree) {
    printf("BITree: ");
    for (int i = 0; i <= tree->size; i++) {
        printf("%d ", tree->values[i]);
    }
    printf("\n");
}