#include "quick.h"
#include "../../_utils_/asserts.h"

int main() {
    {
        int array[] = {5,6,2,50};
        int expected[] = {5,6,2,50};
        int pivot = quick_join(array, 0, 3);
        assertArray(array, expected, 4);
        assert(pivot == 3);
    }


    {
        int array[] = {2,1};
        int expected[] = {1,2};
        int pivot = quick_join(array, 0, 1);
        assert(pivot == 0);
        assertArray(array, expected, 2);
    }

    {
        int array[] = {1,2,3};
        int expected[] = {1,2,3};
        int pivot = quick_join(array, 0, 2);
        assertArray(array, expected, 3);
        assert(pivot == 2);
    }

    {
        int array[] = {4,7,10,5,9};
        int expected[] = {4,7,5,9,10};
        int pivot = quick_join(array, 0, 4);
        assertArray(array, expected, 5);
        assert(pivot == 3);
    }

    {
        int array[] = {4,7,10,5,9};
        int expected[] = {4,5,7,10,9};
        int pivot = quick_join(array, 0, 3);
        assertArray(array, expected, 5);
        assert(pivot == 1);
    }

    {
        size_t array_size = 2;
        int array[] = {7, 1};
        int expected[] = {1, 7};
        assertArray(quick(array, array_size), expected, array_size);
    }

    {
        size_t array_size = 15;
        int array[] = {7, 8, 9, 0, 9, 5, 6, 2, 1, 3, 4, 5, 6, 8, 9};
        int expected[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 9};
        assertArray(quick(array, array_size), expected, array_size);
    }

    // {
    //     size_t array_size = 15;
    //     int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    //     int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    //     assertArray(quick(array, array_size), expected, array_size);
    // }

    // {   
    //     size_t array_size = 15;
    //     int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1};
    //     int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9};
    //     assertArray(quick(array, array_size), expected, array_size);
    // }

    return 0;
}