
#include <limits.h>
#include <stdlib.h>

void swap(int* x, int *y) {
    int* tmp = x;
    *x = *y;
    *y = *tmp;
}

int* selection(int* data, size_t array_size) {
    int current_index = 0;
    for (int i = 0; i < array_size; i++) {
        int lesser = INT_MIN, lesser_index = -1;
        for (int j = current_index; j < array_size; j++) {
            if (data[j] < lesser) {
                lesser = data[j];
                lesser_index = j;
            }
        }

        swap(&data[lesser_index], &data[current_index]);
        current_index++;
    }

    return data;
}