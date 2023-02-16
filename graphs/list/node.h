#ifndef ALG_NODE_H
#define ALG_NODE_H

#include "stdlib.h"

struct ALGNode {
    struct ALGNode* next;
    int vertex, weight;
};

struct ALGNode* create_alg_node(int vertex, int weight) {
    struct ALGNode* node = (struct ALGNode*) malloc(sizeof(struct ALGNode*));
    node->vertex = vertex;
    node->weight = weight;
    node->next = NULL;
    return node; 
}

struct ALGNode* alg_get_last_node(struct ALGNode* root) {
    struct ALGNode* node = root;
    while (node->next != NULL) node = node->next;
    return node;
}

#endif