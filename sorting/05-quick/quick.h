#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int quick_join(int *data, int left, int right) {

    int size = right - left + 1;
    int biggest[size], lowers[size];

    int pivot = data[right];
    int biggest_index = 0, lowers_index = 0;
    for (int i = left; i <= right - 1; i++) {
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

    lowers_index += left;
    data[lowers_index] = pivot;
    index++;
    
    for (int i = 0; i < biggest_index; i++) {
        data[index] = biggest[i];
        index++;
    }

    return lowers_index;
}

int* quick_sort(int* data, int left, int right) {
    if (left < right) {
        int pivot_index = quick_join(data, left, right);
        quick_sort(data, left, pivot_index-1);
        quick_sort(data, pivot_index+1, right);
    }

    return data;
}

int* quick(int* data, size_t array_size) {
    return quick_sort(data, 0, array_size - 1);
}