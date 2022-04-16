#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

void push(struct StackNode** root, char data) {
    struct StackNode* node = new_stack_node(data);
    node->next = *root;
    *root = node;
    printf("Pushing new node %p with data %d\n", node, data);
} 

int is_empty(struct StackNode* root) {
    return !root;
}

char pop(struct StackNode** root) {
    if (is_empty(*root)) {
        return NULL;
    }

    printf("Popping node %p with data %d\n", *root, (*root)->data);

    struct StackNode* previousRoot = *root;
    *root = (*root)->next; 

    int popped = previousRoot->data;
    free(previousRoot);

    return popped;
}

char peek(struct StackNode *root) {
    if (is_empty(root)) {
        return NULL;
    }
    return root->data;
}
