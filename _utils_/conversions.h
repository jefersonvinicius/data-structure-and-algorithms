#ifndef __CONVERSIONS_H
#define __CONVERSIONS_H

#include <stdio.h>
#include <stdlib.h>

int __number_size(int v) {
    if (v == 0) return 1;
    int result = 0;
    for (; v; v /= 10)
        result++;
    return result;
}

char* to_string(int v) {
    int size = __number_size(v);
    char* result = (char*) malloc(size * sizeof(char));
    sprintf(result, "%d", v);
    return result;
}

// create pointer to int value
int* intp(int v) { 
    int* pointer = (int*) malloc(sizeof(int));
    (*pointer) = v;
    return pointer;
}

int* unpointer_ints(int** values, int size) {
    int* result = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) result[i] = *values[i];
    return result;
}

#endif