#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include "conversions.h"

#ifdef TESTING
#define BIG_ARRAY_SIZE 1000 * 10
#else
#define BIG_ARRAY_SIZE 1000 * 100
#endif

int* generate_big_array() {
    int* array = malloc(sizeof(int) * BIG_ARRAY_SIZE);
    for (int i = 0; i < BIG_ARRAY_SIZE; i++) {
        array[i] = (rand() + 100) % 10000;
    }
    return array;
}

#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))

// Make Static Array
#define mksa(...) _make_array(NUMARGS(__VA_ARGS__), __VA_ARGS__)

int* _make_array(int number_of_elements, ...) {
    int* result = (int*) malloc(sizeof(int) * number_of_elements);
    va_list args_list;
    va_start(args_list, number_of_elements);
    for (int i = 0; i < number_of_elements; i++) {
        result[i] = va_arg(args_list, int);
    }
    va_end(args_list);
    return result;
}

// Make Static Array Pointer
#define mksap(...) _make_array_p(NUMARGS(__VA_ARGS__), __VA_ARGS__)
int** _make_array_p(int number_of_elements, ...) {
    int** result = (int**) malloc(sizeof(int) * number_of_elements * sizeof(int*));
    va_list args_list;
    va_start(args_list, number_of_elements);
    for (int i = 0; i < number_of_elements; i++) {
        result[i] = intp(va_arg(args_list, int));
    }
    va_end(args_list);
    return result;
}
