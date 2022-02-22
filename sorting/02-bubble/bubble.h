
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

// Iterate by array to find the comparing the current with next value and swap if the first is bigger, so repeat it
int* bubble(int* data, size_t array_size) {
    for (int i = 0; i < array_size - 1; i++) {
        int swap_something = 0;
        for (int j = 0; j < array_size - i - 1; j++) {
            if (data[j] > data[j+1]) {
                int tmp = data[j+1];
                data[j+1] = data[j];
                data[j] = tmp;
                swap_something = 1;
            }
        }

        if (!swap_something) break;
    }
    return data;
}