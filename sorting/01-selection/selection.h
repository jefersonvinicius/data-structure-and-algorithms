
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

// Iterate by array to find the lesser value and put in start, so repeat it
int* selection(int* data, size_t array_size) {
    for (int i = 0; i < array_size; i++) {
        int lesser = INT_MAX, lesser_index = -1;
        for (int j = i; j < array_size; j++) {
            if (data[j] < lesser) {
                lesser = data[j];
                lesser_index = j;
            }
        }
        int tmp = data[i];
        data[i] = lesser;
        data[lesser_index] = tmp;
    }

    return data;
}