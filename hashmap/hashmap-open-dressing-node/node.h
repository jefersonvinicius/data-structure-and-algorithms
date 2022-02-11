#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node {
    int value;
    char* key;
};

struct Node* create_node(char* key, int value) {
    struct Node* node = malloc(sizeof(struct Node));
    node->key = key;
    node->value = value;
    return node;
}
