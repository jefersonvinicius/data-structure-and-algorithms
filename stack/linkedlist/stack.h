#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

struct LklStackNode {
    int data;
    struct LklStackNode* next;
};

struct LklStack {
    struct LklStackNode* root;
};

struct LklStack* create_lklstack() {
    struct LklStack* stack = (struct LklStack*) malloc(sizeof(struct LklStack*));
    stack->root = NULL;
    return stack;
}

struct LklStackNode* create_lklstack_node(int data) {
    struct LklStackNode *node = (struct LklStackNode*) malloc(sizeof(struct LklStackNode));
    node->data = data;
    node->next = NULL;
    return node;
}


void lkls_push(struct LklStack* stack, int data) {
    struct LklStackNode* node = create_lklstack_node(data);
    node->next = stack->root;
    stack->root = node;
} 

int lkls_is_empty(struct LklStack* stack) {
    return stack->root == NULL;
}

int lkls_pop(struct LklStack* stack) {
    int popped = stack->root->data;
    struct LklStackNode* popped_node = stack->root;
    stack->root = stack->root->next;
    free(popped_node);
    popped_node = NULL;
    return popped;
}

int lkls_top(struct LklStack* stack) {
    return stack->root->data;
}
