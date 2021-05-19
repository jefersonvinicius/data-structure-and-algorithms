#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    char value;
    struct StackNode* next;
};

struct StackNode* create_node(char value) {
    struct StackNode* node = malloc(sizeof(struct StackNode));
    node->value = value;
    node->next = NULL;
    return node;
}

int is_empty(struct StackNode* rootNode) {  
    return rootNode == NULL;
}

void push(struct StackNode** rootNode, char value) {
    if (*rootNode == NULL) {
        *rootNode = create_node(value);
        return;
    }

    struct StackNode* node = create_node(value);
    node->next = *rootNode;
    *rootNode = node;
}

char top(struct StackNode *rootNode) {
    if (is_empty(rootNode)) {
        printf("ERROR ON TOP: empty stack\n");
        return '-';
    }
    return rootNode->value;
}

int main() {
    struct StackNode* stack = NULL;
    push(&stack, 'a');
    push(&stack, 'b');
    printf("TOP: %c\n", top(stack));
}