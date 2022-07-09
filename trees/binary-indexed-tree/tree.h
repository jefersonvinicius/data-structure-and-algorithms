#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BI_TREE_SIZE 10000

struct BITree {
    int* raw;
    int* indexed;
    int size;
};

struct BITree* create_binary_indexed_tree() {
    struct BITree* tree = malloc(sizeof(struct BITree*));
    tree->indexed = malloc(sizeof(int) * MAX_BI_TREE_SIZE);
    tree->raw = malloc(sizeof(int) * MAX_BI_TREE_SIZE);
    memset(tree->indexed, MAX_BI_TREE_SIZE, 0);
    memset(tree->raw, MAX_BI_TREE_SIZE, 0);
    tree->indexed[0] = 0;
    tree->raw[0] = 0;
    tree->size = 1;
    return tree;
};

void bi_insert(struct BITree* tree, int value) {
    int initial_index = tree->size;
    tree->indexed[initial_index] = value;
    tree->raw[initial_index] = value;
    int final_index = initial_index - (initial_index & (-initial_index));
    for  (int i = initial_index - 1; i > final_index; i--) {
        tree->indexed[initial_index] += tree->raw[i];
    }
    tree->size++;
}

int bi_get_sum(struct BITree* tree, int end) {
    int sum = 0, index = end + 1;
    while (index > 0) {
        sum += tree->indexed[index];
        index -= index & (-index);
    }
    return sum;
}

void bi_update(struct BITree* tree, int index, int value) {
    int index = end + 1;
    while (index > 0) {
        tree->indexed[index] = tree->indexed[index];
        index -= index & (-index);
    }
    return sum;
}

int bi_print(struct BITree* tree) {
    printf("- BITree -\n");
    printf("Original: ");
    for (int i = 1; i < tree->size; i++) printf("%d ", tree->raw[i]);
    printf("\nBinary Indexed: ");
    for (int i = 1; i < tree->size; i++) printf("%d ", tree->indexed[i]);    
    printf("\n");
}