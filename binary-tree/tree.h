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

void _count(struct Node* node, int* result) {
    if (node == NULL) return;
    
    (*result)++;
    _count(node->left, result);
    _count(node->right, result);
}

int tree_size(struct Tree* tree) {
    int size = 0;
    struct Node* node = tree->root;
    _count(node, &size);
    return size;
}

void _in_order_recursion(struct Node* root, int* result, int* index) {  
    if (root == NULL) return;
    
    _in_order_recursion(root->left, result, index);
    result[(*index)] = root->value;
    (*index)++;
    _in_order_recursion(root->right, result, index);
}

int* in_order(struct Tree* tree) {
    int index = 0;
    int* result = malloc(sizeof(int) * tree_size(tree));
    _in_order_recursion(tree->root, result, &index);
    return result;
}

void _pre_order_recursion(struct Node* root, int* result, int* index) {  
    if (root == NULL) return;
    
    result[(*index)] = root->value;
    (*index)++;
    _pre_order_recursion(root->left, result, index);
    _pre_order_recursion(root->right, result, index);
}

int* pre_order(struct Tree* tree) {
    int index = 0;
    int* result = malloc(sizeof(int) * tree_size(tree));
    _pre_order_recursion(tree->root, result, &index);
    return result;
}

void _post_order_recursion(struct Node* root, int* result, int* index) {  
    if (root == NULL) return;
    
    _post_order_recursion(root->left, result, index);
    _post_order_recursion(root->right, result, index);
    result[(*index)] = root->value;
    (*index)++;
}

int* post_order(struct Tree* tree) {
    int index = 0;
    int* result = malloc(sizeof(int) * tree_size(tree));
    _post_order_recursion(tree->root, result, &index);
    return result;
}