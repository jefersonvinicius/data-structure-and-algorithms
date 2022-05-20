#include <stdlib.h>

struct Node {
    int value;
    struct Node* right;
    struct Node* left;
};

struct BinarySearchTree {
    struct Node* root;
};

struct BinarySearchTree* create_binary_search_tree() {
    struct BinarySearchTree* tree = (struct BinarySearchTree*) malloc(sizeof(struct BinarySearchTree));
    tree->root = NULL;
    return tree;
}

struct Node* create_node(int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void bst_insert(struct BinarySearchTree* tree, int value) {
    tree->root = create_node(value);
}