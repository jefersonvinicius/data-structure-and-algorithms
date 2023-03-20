#ifndef __COMPARATORS_H
#define __COMPARATORS_H

int intp_equals_int(const void* a, const void* b) {
    printf("CMP; %p - %p\n", a, b);
    printf("B: %d\n", (int) b);
    printf("A: %d\n", *(int*) a);
    printf("IOU\n");
    // printf("CMP: %d\n", *(int*) a);
    return 1;
}

#endif