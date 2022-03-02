#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../_utils_/debug.h"

int* quick_slice(int* data, int start, int end) {
    int* result = malloc(sizeof(int) * (end - start + 1));
    for (int i = start; i <= end; i++) {
        result[i - start] = data[i];
    }
    return result;
}

int *quick_join(int *data, int left, int right) {

    int size = right - left + 1;
    int biggest[size], lowers[size];

    int pivot = data[size-1];
    int biggest_index = 0, lowers_index = 0;
    for (int i = 0; i < size - 1; i++) {
        if (data[i] > pivot) {
            biggest[biggest_index] = data[i];
            biggest_index++;
        } else {
            lowers[lowers_index] = data[i];
            lowers_index++;
        }
    }

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

    return data;
}

int* quick_sort(int* data, int size) {
    
}

// Iterate by array comparing the current value with previous and insert when previous is bigger
int* quick(int* data, size_t array_size) {
    return quick_sort(data, array_size);
}