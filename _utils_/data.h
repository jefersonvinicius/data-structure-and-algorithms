#include <stdlib.h>

#ifdef TESTING
#define BIG_ARRAY_SIZE 1000 * 10
#else
#define BIG_ARRAY_SIZE 1000 * 100
#endif

int* generate_big_array() {
    int* array = malloc(sizeof(int) * BIG_ARRAY_SIZE);
    for (int i = 0; i < BIG_ARRAY_SIZE; i++) {
        array[i] = (rand() + 100) % 10000;
    }
    return array;
}