#include <stdlib.h>

struct Node {
    int value;
    struct Node* right;
    struct Node* left;
};

struct Node* create_node(int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Tree {
    struct Node* root;
};

struct Tree* create_binary_tree() {
    struct Tree* tree = (struct Tree*) malloc(sizeof(struct Tree*));
    return tree; 
}