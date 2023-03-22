#ifndef __COMPARATORS_H
#define __COMPARATORS_H

int intp_equals_intp(const void* a, const void* b) {
    return *(int*) a == *(int*) b;
}

#endif