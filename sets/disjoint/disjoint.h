#include "stdlib.h"

#define MAX_DISJOINT_SET 100000

struct IntDisjointSet {
    int* parent;    
};

struct IntDisjointSet* create_int_disjoint_set() {
    struct IntDisjointSet* set = (struct IntDisjointSet*) malloc(sizeof(struct IntDisjointSet));
    set->parent = (int*) malloc(MAX_DISJOINT_SET * sizeof(int));
    for (int i = 0; i < MAX_DISJOINT_SET; i++) set->parent[i] = i;
    return set;
}

int int_disjoint_set_find(struct IntDisjointSet* set, int i) {
    if (set->parent[i] == i) return i;
    return int_disjoint_set_find(set, set->parent[i]);
}

void int_disjoint_set_union(struct IntDisjointSet* set, int a, int b) {
    int a_parent = int_disjoint_set_find(set, a);
    int b_parent = int_disjoint_set_find(set, b);
    set->parent[b_parent] = a_parent;
}

int int_disjoint_set_has(struct IntDisjointSet* set, int a, int b) {
    return int_disjoint_set_find(set, a) == int_disjoint_set_find(set, b);
}