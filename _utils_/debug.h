#include <stdio.h>

void debug_int_array(int* array, int array_size ) {
    printf("DEBUGGING ARRAY ALLOCATED AT: %p\n", &(*array));
    for (int i = 0; i < array_size; i++) {
        int value = array[i];
        if (i == array_size - 1) printf("[%d] %d\n", i, value);
        else printf("[%d] %d -> ", i, value);
    } 
}