#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack/stackfortree.h"
#include "math/algorithms.h"

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

struct NodeChar* create_node_char(char* value) {
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

int _maxchar_depth(struct NodeChar* node) {
    if (node == NULL) return -1;
    
    int max_right = _maxchar_depth(node->right);
    int max_left = _maxchar_depth(node->left);
    return (max_left > max_right ? max_left : max_right) + 1;
}

int treechar_height(struct TreeChar* tree) {
    return _maxchar_depth(tree->root) + 1;
}

void _print_level(struct NodeChar* node, int level, int original_level, char** levels) {
    if (node == NULL) return;

    if (level == 1) {
        char *c = malloc(strlen(node->value) * sizeof(char));
        strcat(c, node->value);
        strcat(c, "&");
        strcat(levels[original_level - 1], c);
    } else if (level > 1) {
        _print_level(node->left, level - 1, original_level, levels);
        _print_level(node->right, level - 1, original_level, levels);
    }
}

void print_tree(struct TreeChar* tree) {
    int tree_height = treechar_height(tree);
    char** levels = malloc(tree_height * sizeof(char*));
    for (int i = 0; i < tree_height; i++) {
        levels[i] = malloc(100 * sizeof(char));
    }

    for (int i = 1; i <= tree_height; i++) {
        _print_level(tree->root, i, i, levels);
    }

    for (int i = 0; i < tree_height; i++) {
        printf("Level %d: %s\n", i+1, levels[i]);
        char* part;
        part = strtok(levels[i], "&");

        while (part != NULL) {
            printf("Part: %s\n", part);
            part = strtok(NULL, "&");
        }
    }
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
    int* result = (int*) malloc(sizeof(int) * tree_size(tree));
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
    int* result = (int*) malloc(sizeof(int) * tree_size(tree));
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
    int* result = (int*) malloc(sizeof(int) * tree_size(tree));
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

int _max_depth(struct Node* node) {
    if (node == NULL) return -1;
    
    int max_right = _max_depth(node->right);
    int max_left = _max_depth(node->left);
    return (max_left > max_right ? max_left : max_right) + 1;
}

int tree_height(struct Tree* tree) {
    return _max_depth(tree->root) + 1;
}

void _current_level(struct Node* node, int level, int* result, int* result_index) {
    if (node == NULL) return;
    if (level == 1) {
        result[*result_index] = node->value;
        (*result_index)++;
    } else if (level > 1) {
        _current_level(node->left, level - 1, result, result_index);
        _current_level(node->right, level - 1, result, result_index);
    }
}

int* level_order(struct Tree* tree) {
    int* result = malloc(sizeof(int) * tree_size(tree) + sizeof(int));
    int result_index = 0;
    for (int i = 1; i <= tree_height(tree); i++) {
        _current_level(tree->root, i, result, &result_index);
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

int _is_operator(char* c) {
    return *c == '+' || *c == '-' || *c == '/' || *c == '*';
}

struct TreeChar* build_tree_expression(char* expression) {
    
    struct PostFixResult* postfix_result = infix_to_postfix(expression);

    char** postfix = postfix_result->postfix;

    struct StackTreeNode* stack = NULL;
    for (int i = 0; i < postfix_result->size; i++) {
        char* current = postfix[i]; 

        if (_is_operator(current)) {
            struct NodeChar* pop1 = stacktree_pop(&stack);
            struct NodeChar* pop2 = stacktree_pop(&stack);
            struct NodeChar* root = create_node_char(current);
            root->left = pop2;
            root->right = pop1;
            stacktree_push(&stack, root);
        } else {
            stacktree_push(&stack, create_node_char(current));
        }
    }

    struct TreeChar* tree = create_binary_tree_char();
    tree->root = stacktree_top(stack);    

    return tree;
}

int _calculate(int a, int b, char operator) {
    switch (operator)
    {
        case '+':
            return a + b;
            break;
        case '-':
            return a - b;
            break;
        case '*':
            return a * b;
            break;
        case '/':
            return a / b;
            break;
        default:
            break;
    }
}

int _solve_part(struct NodeChar* node) {
    if (node != NULL) {
        if (!_is_operator(node->value)) {
            return atoi(node->value);
        } 

        int a = _solve_part(node->left);
        int b = _solve_part(node->right);

        return _calculate(a, b, *node->value);
    }
}

int solve_expression_with_tree(char* expression) {
    struct TreeChar* tree = build_tree_expression(expression);
    return _solve_part(tree->root);
}