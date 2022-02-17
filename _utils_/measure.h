#include <stdio.h>
#include <time.h>

double measure_function_speed(char *label, void (*fn)()) {
    clock_t begin = clock();
    fn();
    clock_t end = clock();
    double speed = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("%s runs in %f s\n", label, speed);
    return speed;
}