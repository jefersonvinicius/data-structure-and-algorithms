#include <stdio.h>
#include <assert.h>
#include <vector>
#include "../_utils_/asserts.h"

#include "tree.h"

using namespace std;


void in_order_recursion(struct Node* root) {    
    if (root == NULL) return;
    
    in_order_recursion(root->left);
    printf("%d ", root->value);
    in_order_recursion(root->right);
}

int main() {

    struct Tree* tree = create_binary_tree();
    tree->root = create_node(1);
    tree->root->left = create_node(2);
    tree->root->right = create_node(3);
    tree->root->left->left = create_node(4);
    tree->root->left->right = create_node(5);
    tree->root->right->left = create_node(6);

    in_order_recursion(tree->root);
    printf("\n");

    return 0;
}