#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

void assertArray(int* actual_array, int* expected_array, size_t expected_size) {
    for (int i = 0; i < expected_size; i++) {
        if (actual_array[i] != expected_array[i]) {
            printf("At index [%d] expected (%d), but got (%d)\n", i, expected_array[i], actual_array[i]);
            exit(EXIT_FAILURE);
        }
    }
}