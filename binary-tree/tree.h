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

int _index_of(int* data, size_t size_data, int target) {
    int result = -1;
    for (int i = 0; i < size_data; i++) {
        if (data[i] == target) {
            result = i;
            break;
        }
    }
    return result;
}

struct Node* _build(int* pre_order_data, int* in_order_data, int left, int right, int pre_index) {
    if (left < right) {
        printf("left: %d - right: %d\n", left, right);
        int size = right - left + 1;
        int element = pre_order_data[pre_index];
        struct Node* root = create_node(element);
        int in_index = _index_of(in_order_data, size, element);

        struct Node* left = _build(pre_order_data, in_order_data, pre_index, in_index - 1, pre_index + 1);
        struct Node* right = _build(pre_order_data, in_order_data, in_index + 1, size, pre_index + 1);

        if (left != NULL) root->left = left;
        if (right != NULL) root->right = right;
        return root;
    }   
}

struct Tree* build_tree_from_pre_and_in_order(int* pre_order_data, int* in_order_data, size_t size) {
    struct Tree* result = create_binary_tree();

    int pre_index = 0, in_index = 0;

    int element = pre_order_data[pre_index];
    struct Node* root = create_node(element);
    in_index = _index_of(in_order_data, size, element);

    struct Node* left = _build(pre_order_data, in_order_data, 0, in_index - 1, pre_index + 1);
    struct Node* right = _build(pre_order_data, in_order_data, in_index + 1, size, pre_index + 1);

    root->left = left;
    root->right = right;
    result->root = root;

    return result;
}