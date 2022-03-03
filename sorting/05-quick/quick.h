#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../_utils_/debug.h"

int quick_join(int *data, int left, int right) {

    int size = right - left + 1;
    int biggest[size], lowers[size];

    int pivot = data[right];
    int biggest_index = 0, lowers_index = 0;
    // printf("pivot: %d\n", pivot);
    for (int i = left; i < right; i++) {
        // printf("%d ", data[i]);
        if (data[i] > pivot) {
            biggest[biggest_index] = data[i];
            biggest_index++;
        } else {
            lowers[lowers_index] = data[i];
            lowers_index++;
        }
    }
    // printf("\n");
    // debug_int_array(lowers,lowers_index);
    // debug_int_array(biggest, biggest_index);

    int index = left;
    for (int i = 0; i < lowers_index; i++) {
        data[index] = lowers[i];
        index++;
    }

    data[lowers_index] = pivot;
    index++;
    
    for (int i = 0; i < biggest_index; i++) {
        data[index] = biggest[i];
        index++;
    }

    return lowers_index;
}

int* quick_sort(int* data, int left, int right) {
    printf("left: %d, right: %d\n", left, right);
    if (left < right) {
        int pivot_index = quick_join(data, left, right);
        printf("pivot: %d\n", pivot_index);
        quick_sort(data, left, pivot_index);
        quick_sort(data, pivot_index+1, right);
    }

    return data;
}

// Iterate by array comparing the current value with previous and insert when previous is bigger
int* quick(int* data, size_t array_size) {
    return quick_sort(data, 0, array_size - 1);
}