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
        struct PostFixResult* result = infix_to_postfix("40 * 10 - ( 60 + 240 ) + 810 / ( 91 - 7 )");
        assert(result->size == 13);
        assert(strcmp(result->postfix[0], "40") == 0);
        assert(strcmp(result->postfix[1], "10") == 0);
        assert(strcmp(result->postfix[2], "*") == 0);
        assert(strcmp(result->postfix[3], "60") == 0);
        assert(strcmp(result->postfix[4], "240") == 0);
        assert(strcmp(result->postfix[5], "+") == 0);
        assert(strcmp(result->postfix[6], "-") == 0);
        assert(strcmp(result->postfix[7], "810") == 0);
        assert(strcmp(result->postfix[8], "91") == 0);
        assert(strcmp(result->postfix[9], "7") == 0);
        assert(strcmp(result->postfix[10], "-") == 0);
        assert(strcmp(result->postfix[11], "/") == 0);
        assert(strcmp(result->postfix[12], "+") == 0);
        assert(strcmp(flat_string_array(result->postfix, 13), "4010*60240+-810917-/+") == 0);
    }

    { // should get correct infix
        struct PostFixResult* result = infix_to_postfix("4 * a - ( 6 + b ) + 8 / ( 9 - 7 )");
        assert(result->size == 13);
        assert(strcmp(result->postfix[0], "4") == 0);
        assert(strcmp(result->postfix[1], "a") == 0);
        assert(strcmp(result->postfix[2], "*") == 0);
        assert(strcmp(result->postfix[3], "6") == 0);
        assert(strcmp(result->postfix[4], "b") == 0);
        assert(strcmp(result->postfix[5], "+") == 0);
        assert(strcmp(result->postfix[6], "-") == 0);
        assert(strcmp(result->postfix[7], "8") == 0);
        assert(strcmp(result->postfix[8], "9") == 0);
        assert(strcmp(result->postfix[9], "7") == 0);
        assert(strcmp(result->postfix[10], "-") == 0);
        assert(strcmp(result->postfix[11], "/") == 0);
        assert(strcmp(result->postfix[12], "+") == 0);
        assert(strcmp(flat_string_array(result->postfix, 13), "4a*6b+-897-/+") == 0);
    }

    return 0;
}