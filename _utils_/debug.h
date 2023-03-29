#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void debug_int_array(int* array, int array_size ) {
    printf("DEBUGGING ARRAY ALLOCATED AT: %p\n", &(*array));
    for (int i = 0; i < array_size; i++) {
        int value = array[i];
        if (i == array_size - 1) printf("[%d] %d\n", i, value);
        else printf("[%d] %d -> ", i, value);
    } 
}

void wait_key() {
    pid_t pid = getpid();
    printf("Waiting Enter for %u process\n", pid);
    char c; scanf("%c", &c);
}

#ifdef DEBUG
#define debug_log(__fmt, ...) printf(__fmt, ##__VA_ARGS__);
#endif

#ifndef DEBUG
#define debug_log(__fmt, ...) 
#endif

#endif