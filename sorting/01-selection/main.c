#include "selection.h"
#include "../../_utils_/asserts.h"

int main() {
    size_t array_size = 15;
    int array1[] = {7, 8, 9, 0, 9, 5, 6, 2, 1, 3, 4, 5, 6, 8, 9};
    int expected1[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 9};
    assertArray(selection(array1, array_size), expected1, array_size);

    int array2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int expected2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    assertArray(selection(array2, array_size), expected2, array_size);
    
    return 0;
}