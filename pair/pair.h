#ifndef __PAIR_HEADER
#define __PAIR_HEADER

#include "stdlib.h"

struct Pair {
    void* left;
    void* right;
};

struct Pair* make_pair(void* left, void* right) {
    struct Pair* pair = malloc(sizeof(struct Pair));
    pair->left = left;
    pair->right = right;
    return pair;
}

#endif