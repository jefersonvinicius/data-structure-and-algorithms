#include <stdio.h>
#include <assert.h>
#include "./binary-search-tree.h"
#include "../../_utils_/data.h"
#include "../../_utils_/measure.h"

struct BinarySearchTree* tree;
int target;
struct Node* result;

void run() {
    result = bst_search(tree, target);
}

int main() {

    tree = create_binary_search_tree();
    int* data = generate_big_array();
    for (int i = 0; i < BIG_ARRAY_SIZE; i++) {
        if (i == BIG_ARRAY_SIZE / 2) target = data[i];
        bst_insert(tree, data[i]);
    }

    printf("Searching for: %d\n", target);
    measure_function_speed("BST Search Time", run);
    printf("Node found: %p\n", result);

    return 0;
}