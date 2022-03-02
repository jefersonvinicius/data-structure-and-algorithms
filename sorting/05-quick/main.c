#include "quick.h"
#include "../../_utils_/asserts.h"

int main() {
    int array5[] = {2,1};
    int expected5[] = {1,2};
    assertArray(quick_join(array5, 0, 1), expected5, 2);

    int array6[] = {1,2,3};
    int expected6[] = {1,2,3};
    assertArray(quick_join(array6, 0, 2), expected6, 3);

    int array7[] = {4,7,10,5,9};
    int expected7[] = {4,7,5,9,10};
    assertArray(quick_join(array7, 0, 4), expected7, 5);

    int array4[] = {5,6,2,50};
    int expected4[] = {5,6,2,50};
    assertArray(quick_join(array4, 0, 3), expected4, 4);

    size_t array_size = 15;
    int array1[] = {7, 8, 9, 0, 9, 5, 6, 2, 1, 3, 4, 5, 6, 8, 9};
    int expected1[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 9};
    assertArray(quick(array1, array_size), expected1, array_size);

    int array2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int expected2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    assertArray(quick(array2, array_size), expected2, array_size);
    
    int array3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1};
    int expected3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9};
    assertArray(quick(array3, array_size), expected3, array_size);


    return 0;
}