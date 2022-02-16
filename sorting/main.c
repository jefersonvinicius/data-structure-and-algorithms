#include <stdio.h>
#include <time.h>
#include "../_utils_/measure.h"


void test() {
    int n = 1000*1000*1000;
    while (--n) {}
}

void test2() {
    int n = 1000*1000;
    while (--n) {}
}

int main() {

    measure_function_speed("test", test);
    measure_function_speed("test 2", test2);

    return 0;
}