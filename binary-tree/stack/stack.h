#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

struct StackNode {
    char data;
    struct StackNode* next;
};

struct StackNode* new_stack_node(char data) {
    struct StackNode *node = malloc(sizeof(struct StackNode));
    node->data = data;
    node->next = NULL;
    return node;
}

int is_empty(struct StackNode* root) {
    return root == NULL;
}

char* top(struct StackNode *rootNode) {
    if (is_empty(rootNode)) {
        return NULL;    
    }
    return &rootNode->data;
}

void push(struct StackNode** root, char data) {
    struct StackNode* node = new_stack_node(data);
    node->next = *root;
    *root = node;
} 

char* pop(struct StackNode** root) {
    if (is_empty(*root)) {
        return NULL;
    }

    struct StackNode* previousRoot = *root;
    *root = (*root)->next; 

    char popped = previousRoot->data;
    free(previousRoot);

    char* value = malloc(sizeof(popped));
    *value = popped;

    return value;
}
