#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "conversions.h"

void __print_array(int* array, int size, int index_fail) {
    printf("    ");
    for (int i = 0; i < size; i++) {
        if (i == index_fail) {
            printf("\e[4m%d\e[0m ", array[i]);
        } else {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}

void __print_error_indicator(int* actual_array, int* expected_array, int size, int index_fail) {
    printf("    ");
    for (int i = 0; i < size; i++) {
        if (i == index_fail) {
            printf("*");
        } else {
            char* expect_value_str = to_string(expected_array[i]);
            char* actual_value_str = to_string(actual_array[i]);
            char* bigger = strlen(expect_value_str) > strlen(actual_value_str) ? expect_value_str : actual_value_str;
            for (int i = 0; i < strlen(bigger); i++)
                printf(" ");
            printf(" ");
        }
    }
    printf("\n");
}

void __assert_array(int* actual_array, int* expected_array, size_t expected_size, char const * file, int line) {
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    for (int i = 0; i < expected_size; i++) {
        if (actual_array[i] != expected_array[i]) {
            printf("Assert array fail in %s/%s:%d\n", cwd, file, line);
            printf("    At index [%d] expected (%d), but got (%d)\n", i, expected_array[i], actual_array[i]);
            __print_array(actual_array, expected_size, i);
            __print_array(expected_array, expected_size, i);
            __print_error_indicator(actual_array, expected_array, expected_size, i);
            exit(EXIT_FAILURE);
        }
    }
}

#define assert_array(actual_array, expected_array, array_size) __assert_array(actual_array, expected_array, array_size, __FILE__, __LINE__)
