#include <stdlib.h>
#include "stack/stack.h"

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

struct NodeChar {
    char value;
    struct NodeChar* right;
    struct NodeChar* left;
};

struct NodeChar* create_node_char(char value) {
    struct NodeChar* node = (struct NodeChar*) malloc(sizeof(struct NodeChar));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeChar {
    struct NodeChar* root;
};

struct TreeChar* create_binary_tree_char() {
    struct TreeChar* tree = (struct TreeChar*) malloc(sizeof(struct TreeChar*));
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

int _index_of(int* data, int left, int right, int target) {
    int result = -1;
    for (int i = left; i <= right; i++) {
        if (data[i] == target) {
            result = i;
            break;
        }
    }
    return result;
}

struct Node* _build(int* pre_order_data, int* in_order_data, int left, int right, int *pre_index) {
    if (left <= right) {
        (*pre_index)++;
        int element = pre_order_data[*pre_index];
        struct Node* root = create_node(element);
        int in_index = _index_of(in_order_data, left, right, element);

        struct Node* left_node = _build(pre_order_data, in_order_data, left, in_index - 1, pre_index);
        struct Node* right_node = _build(pre_order_data, in_order_data, in_index + 1, right, pre_index);
        
        if (left_node != NULL) root->left = left_node;
        if (right_node != NULL) root->right = right_node;

        return root;
    }
    return NULL;
}

struct Tree* build_tree_from_pre_and_in_order(int* pre_order_data, int* in_order_data, size_t size) {
    struct Tree* result = create_binary_tree();

    int pre_index = 0;

    int element = pre_order_data[pre_index];
    struct Node* root = create_node(element);
    int in_index = _index_of(in_order_data, 0, size - 1, element);

    struct Node* left = _build(pre_order_data, in_order_data, 0, in_index - 1, &pre_index);
    struct Node* right = _build(pre_order_data, in_order_data, in_index + 1, size - 1, &pre_index);

    if (left != NULL) root->left = left;
    if (right != NULL) root->right = right;
    
    result->root = root;

    return result;
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*';
}

struct TreeChar* build_tree_expression(char* expression) {
    struct NodeChar* root = NULL;
    struct StackNode* stack = NULL;

    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] == ' ') continue;

        if (is_operator(expression[i])) {
            struct StackNode* a = pop(stack);
            struct StackNode* b = pop(stack);
            struct Node* node = create_node_char(expression[i]);
            node->left = create_node_char(a->data);
            node->right = create_node_char(b->data);
            if (root == NULL) {
                root = node;
            } else {
                root = node->left;
            }
        } else {
            if (stack == NULL) {
                stack = new_stack_node(expression[i]);
            } else {
                push(stack, expression[i]);
            }
        }
    }
    
    struct TreeChar* tree = create_binary_tree_char();
    tree->root = root;

    return tree;
}