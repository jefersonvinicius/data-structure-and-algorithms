#include "quick.h"
#include "../../_utils_/asserts.h"

int main() {
    {
        int array[] = {5,6,2,50};
        int expected[] = {5,6,2,50};
        int pivot_index = quick_join(array, 0, 3);
        assert_array(array, expected, 4);
        assert(pivot_index == 3);
    }

    {
        int array[] = {5,6,2,50};
        int expected[] = {2,5,6,50};
        int pivot_index = quick_join(array, 0, 2);
        assert_array(array, expected, 4);
        assert(pivot_index == 0);
    }

    {
        int array[] = {5,6,2,50,8,1,2,3,4};
        int expected[] = {5,6,2,8,50,1,2,3,4};
        int pivot_index = quick_join(array, 2, 4);
        assert_array(array, expected, 9);
        assert(pivot_index == 3);
    }

    {
        int array[] = {2,1};
        int expected[] = {1,2};
        int pivot = quick_join(array, 0, 1);
        assert(pivot == 0);
        assert_array(array, expected, 2);
    }

    {
        int array[] = {1,2,3};
        int expected[] = {1,2,3};
        int pivot = quick_join(array, 0, 2);
        assert_array(array, expected, 3);
        assert(pivot == 2);
    }

    {
        int array[] = {4,7,10,5,9};
        int expected[] = {4,7,5,9,10};
        int pivot = quick_join(array, 0, 4);
        assert_array(array, expected, 5);
        assert(pivot == 3);
    }

    {
        int array[] = {4,7,10,5,9};
        int expected[] = {4,5,7,10,9};
        int pivot = quick_join(array, 0, 3);
        assert_array(array, expected, 5);
        assert(pivot == 1);
    }

    {
        int array[] = {7, 1};
        int expected[] = {1, 7};
        assert_array(quick(array, 2), expected, 2);
    }

    {
        int array[] = {7, 1, 10};
        int expected[] = {1, 7, 10};
        assert_array(quick(array, 3), expected, 3);
    }

    {
        int array[] = {7, 8, 0, 10, 20, 10, 10};
        int expected[] = {0, 7, 8, 10, 10, 10, 20};
        assert_array(quick(array, 7), expected, 7);
    }

    {
        int array[] = {7, 8, 9, 0, 9, 5, 6, 2, 1, 3, 4, 5, 6, 8, 9};
        int expected[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 9};
        assert_array(quick(array, 15), expected, 15);
    }

    {
        size_t array_size = 15;
        int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        assert_array(quick(array, array_size), expected, array_size);
    }

    {   
        size_t array_size = 15;
        int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1};
        int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9};
        assert_array(quick(array, array_size), expected, array_size);
    }

    return 0;
}