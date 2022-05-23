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

void _insert_at_node(struct Node* node, int value) {
    if (value > node->value) {
        if (node->right == NULL) node->right = create_node(value);
        else _insert_at_node(node->right, value);
    } else {
        if (node->left == NULL) node->left = create_node(value);
        else _insert_at_node(node->left, value);
    }
}

void bst_insert(struct BinarySearchTree* tree, int value) {
    if (tree->root == NULL) {
        tree->root = create_node(value);
        return;
    }

    _insert_at_node(tree->root, value);
}

struct Node* _search(struct Node* node, int target) {
    if (node == NULL || node->value == target) return node;
    if (target > node->value) return _search(node->right, target);
    return _search(node->left, target);
}

struct Node* bst_search(struct BinarySearchTree* tree, int target) {
    return _search(tree->root, target);
}