#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "algorithms.h"

char* flat_string_array(char* array[], int size) {
    char* result = malloc(0);
    for (int i = 0; i < size; i++) {
        strcat(result, array[i]);
    }
    return result;
}

int main() {

    { // should get correct infix even when has number with 2 or more digits
        // char** result = infix_to_postfix("40 * 10 - ( 60 + 240 ) + 810 / ( 91 - 7 )");
        // assert(strcmp(result[0], "40") == 0);
        // assert(strcmp(result[1], "10") == 0);
        // assert(strcmp(result[2], "*") == 0);
        // assert(strcmp(result[3], "60") == 0);
        // assert(strcmp(result[4], "240") == 0);
        // assert(strcmp(result[5], "+") == 0);
        // assert(strcmp(result[6], "-") == 0);
        // assert(strcmp(result[7], "810") == 0);
        // assert(strcmp(result[8], "91") == 0);
        // assert(strcmp(result[9], "7") == 0);
        // assert(strcmp(result[10], "-") == 0);
        // assert(strcmp(result[11], "/") == 0);
        // assert(strcmp(result[12], "+") == 0);
        // assert(strcmp(flat_string_array(result, 13), "4010*60240+-810917-/+") == 0);
    }

    { // should get correct infix
        char** result = infix_to_postfix("4 * a - ( 6 + b ) + 8 / ( 9 - 7 )");
        printf("result[1] = %s\n", result[1]);
        assert(strcmp(result[0], "4") == 0);
        assert(strcmp(result[1], "a") == 0);
        assert(strcmp(result[2], "*") == 0);
        assert(strcmp(result[3], "6") == 0);
        assert(strcmp(result[4], "b") == 0);
        assert(strcmp(result[5], "+") == 0);
        assert(strcmp(result[6], "-") == 0);
        assert(strcmp(result[7], "8") == 0);
        assert(strcmp(result[8], "9") == 0);
        assert(strcmp(result[9], "7") == 0);
        assert(strcmp(result[10], "-") == 0);
        assert(strcmp(result[11], "/") == 0);
        assert(strcmp(result[12], "+") == 0);
        assert(strcmp(flat_string_array(result, 13), "4a*6b+-897-/+") == 0);
    }

    return 0;
}