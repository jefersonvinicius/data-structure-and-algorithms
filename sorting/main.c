#include <stdio.h>
#include <time.h>

#include "01-selection/selection.h"
#include "02-bubble/bubble.h"
#include "../_utils_/measure.h"
#include "../_utils_/data.h"

int* data = NULL;

int* get_data_copy() {
    int* copy = malloc(sizeof(int) * BIG_ARRAY_SIZE);
    for (int i = 0; i < BIG_ARRAY_SIZE; i++) {
        copy[i] = data[i];
    }
    return copy;
}

void test_selection() {
    selection(get_data_copy(), BIG_ARRAY_SIZE);
}

void test_bubble() {
    bubble(get_data_copy(), BIG_ARRAY_SIZE);
}


int main() {
    printf("Generating data...\n");
    data = generate_big_array();
    printf("Data generated!\n\n");

    measure_function_speed("Selection Sort Algorithm", test_selection);
    measure_function_speed("Bubble Sort Algorithm", test_bubble);

    return 0;
}