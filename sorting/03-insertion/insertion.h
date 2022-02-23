#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../_utils_/debug.h"

// Iterate by array comparing the current value with previous and insert when previous is bigger
int* insertion(int* data, size_t array_size) {
    for (int i = 1; i < array_size; i++) {
        int target = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > target) {
            data[j + 1] = data[j];
            j--;
        }

        data[j + 1] = target;
    }

    return data;
}