#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "../nodes/nodechar.h"

struct StackTreeNode {
    struct NodeChar* node;
    struct StackTreeNode* next;
};

struct StackTreeNode* new_treestack_node(struct NodeChar* data) {
    struct StackTreeNode *node = (struct StackTreeNode*) malloc(sizeof(struct StackTreeNode));
    node->node = data;
    node->next = NULL;
    return node;
}

int stacktree_is_empty(struct StackTreeNode* root) {
    return root == NULL;
}

struct NodeChar* stacktree_top(struct StackTreeNode *rootNode) {
    if (stacktree_is_empty(rootNode)) {
        return NULL;    
    }
    return rootNode->node;
}

void stacktree_push(struct StackTreeNode** root, struct NodeChar* tree_node) {
    struct StackTreeNode* node = new_treestack_node(tree_node);
    node->next = *root;
    *root = node;
} 

struct NodeChar* stacktree_pop(struct StackTreeNode** root) {
    if (stacktree_is_empty(*root)) {
        return NULL;
    }

    struct StackTreeNode* previous_root = *root;
    *root = (*root)->next; 

    struct NodeChar* popped = previous_root->node;
    free(previous_root);

    struct NodeChar* value = (struct NodeChar*) malloc(sizeof(popped));
    value = popped;

    return value;
}
