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

void bst_insert_many(struct BinarySearchTree* tree, int* values, size_t values_size) {
    for (int i = 0; i < values_size; i++) {
        bst_insert(tree, values[i]);
    }
}

struct Node* _search(struct Node* node, int target) {
    if (node == NULL || node->value == target) return node;
    if (target > node->value) return _search(node->right, target);
    return _search(node->left, target);
}

struct Node* bst_search(struct BinarySearchTree* tree, int target) {
    return _search(tree->root, target);
}

void _inorder(struct Node* node, int* result, int* index) {
    if (node != NULL) {
        _inorder(node->left, result, index);
        result[*index] = node->value;
        (*index)++;
        _inorder(node->right, result, index);
    }
}

int* bst_inorder(struct BinarySearchTree* tree) {
    int* result = malloc(sizeof(int) * 10000);
    int index = 0;
    _inorder(tree->root, result, &index);
    return result;
}

struct Node** _find_largest_subnode(struct Node** initial) {
    printf("Checking: %d\n", (*initial)->value);
    if ((*initial)->right == NULL) return initial;
    return _find_largest_subnode(&(*initial)->right);   
}

int _has_none_children(struct Node* node) {
    return node->left == NULL && node->right == NULL;
}

void _delete(struct Node** node, int target) {
    if ((*node)->value == target) {
        if (_has_none_children(*node)) {
            (*node) = NULL;
            free(*node);
        } else if ((*node)->left != NULL && (*node)->right == NULL) {
            struct Node* tmp = (*node);
            (*node) = (*node)->left;
            free(tmp);
        } else if ((*node)->left == NULL && (*node)->right != NULL) {
            struct Node* tmp = (*node);
            (*node) = (*node)->right;
            free(tmp);
        } else {
            struct Node** largest = _find_largest_subnode(&(*node)->left);
            if (_has_none_children(*largest)) {
                (*node)->value = (*largest)->value;
                *largest = NULL;
                free(*largest);
            }
        }
    } else if ((*node)->left != NULL && target <= (*node)->left->value) {
        _delete(&(*node)->left, target);
    } else if ((*node)->right != NULL) {
        _delete(&(*node)->right, target);
    }
}

void bst_delete(struct BinarySearchTree* tree, int value) {
    _delete(&tree->root, value);
}