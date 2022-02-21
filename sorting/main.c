#include <stdio.h>
#include <time.h>

#include "selection/selection.h"
#include "../_utils_/measure.h"
#include "../_utils_/data.h"

int* data = NULL;

void test_selection() {
    selection(data, BIG_ARRAY_SIZE);
}


int main() {
    printf("Generating data...\n");
    data = generate_big_array();
    printf("Data generated!\n\n");

    measure_function_speed("Selection Algorithm", test_selection);

    return 0;
}