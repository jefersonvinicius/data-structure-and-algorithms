#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int* slice(int* data, int start, int end) {
    int* result = malloc(sizeof(int) * (end - start + 1));
    for (int i = start; i <= end; i++) {
        result[i - start] = data[i];
    }
    return result;
}

int *join(int *data, int left, int middle, int right) {
    int left_side_size = middle - left + 1;
    int right_side_size = right - middle;
    int* left_side = slice(data, left, middle);
    int* right_side = slice(data, middle+1, right);
    
    int current_left_index = 0, current_right_index = 0, index = left;
    while (current_left_index < left_side_size && current_right_index < right_side_size) {
        int current_left = left_side[current_left_index];
        int current_right = right_side[current_right_index];
        if (current_left < current_right) {
            data[index] = current_left;
            current_left_index++;
        } else {
            data[index] = current_right;
            current_right_index++;
        }
        index++;
    }

    while (current_left_index < left_side_size) {
        data[index] = left_side[current_left_index];
        current_left_index++;
        index++;
    }

    while (current_right_index < right_side_size) {
        data[index] = right_side[current_right_index];
        current_right_index++;
        index++;
    }

    free(left_side);
    free(right_side);

    return data;
}

int* mergeSort(int* data, int left_index, int right_index) {
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