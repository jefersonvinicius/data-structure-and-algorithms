#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int* slice(int* data, int start, int end) {
    int* result[end - start + 1];
    for (int i = start; i < end; i++) {
        result[i] = data[start+i];
    }
    return result;
}

int *join(int *data, int left, int middle, int right) {
    int* left_side = slice(data, left, middle);
    int* right_side = slice(data, middle+1, right);
}

int* mergeSort(int* data, int left_index, int right_index) {
    printf("mergeSort: %d %d\n", left_index, right_index);
    if (left_index < right_index) {
        int middle = (right_index + left_index) / 2;
        mergeSort(data, left_index, middle);
        mergeSort(data, middle + 1, right_index);
        join(data, left_index, middle, right_index);
    }
}

// Iterate by array comparing the current value with previous and insert when previous is bigger
int* merge(int* data, size_t array_size) {
    return mergeSort(data, 0, array_size - 1);
}