#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

struct StackNode {
    int data;
    struct StackNode* next;
};

struct StackNode* newNode(int data) {
    struct StackNode *node = malloc(sizeof(struct StackNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void push(struct StackNode** root, int data) {
    struct StackNode* node = newNode(data);
    node->next = *root;
    *root = node;
    printf("Pushing new node %p with data %d\n", node, data);
} 

int isEmpty(struct StackNode* root) {
    return !root;
}

int pop(struct StackNode** root) {
    if (isEmpty(*root)) {
        printf("Unable pop: stack empty\n");
        return INT_MIN;
    }

    printf("Popping node %p with data %d\n", *root, (*root)->data);

    struct StackNode* previousRoot = *root;
    *root = (*root)->next; 

    int popped = previousRoot->data;
    free(previousRoot);

    return popped;
}

int peek(struct StackNode *root) {
    if (isEmpty(root)) {
        printf("Unable get peek: stack empty\n");
        return INT_MIN;
    }
    return root->data;
}

int main() {

    struct StackNode* root = newNode(1);
    // printf("Root address: %p\n", &*root);
    push(&root, 2);
    // printf("Root address: %p\n", &*root);
    push(&root, 3);
    // printf("Root address: %p\n", &*root);

    printf("Top: %d\n", peek(root));

    pop(&root);

    printf("Top: %d\n", peek(root));

    pop(&root);
    pop(&root);

    printf("Top: %d\n", peek(root));

    push(&root, 80);

    printf("Top: %d\n", peek(root));


    return 0;
}