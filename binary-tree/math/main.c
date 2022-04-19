#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "algorithms.h"

int main() {

    { // should get correct infix
        const char* result = infix_to_postfix("4 * a - ( 6 + b ) + 8 / ( 9 - 7 )");
        assert(strcmp(result, "4a*6b+-897-/+") == 0);
    }

    return 0;
}