#ifndef ALG_NODE_H
#define ALG_NODE_H

#include "stdlib.h"

struct ALGNode {
    struct ALGNode* next;
    int vertex;
};

struct ALGNode* create_alg_node(int vertex) {
    struct ALGNode* node = malloc(sizeof(struct ALGNode*));
    node->vertex = vertex;
    node->next = NULL;
    return node; 
}

struct ALGNode* get_last_node(struct ALGNode* root) {
    struct ALGNode* node = root;
    printf("NODEE: %p, %p\n", node, node->next);

    // printf("NODEE: %p, %d\n", node, node->vertex);
    while (node->next != NULL) node = node->next;
    return node;
}

#endif