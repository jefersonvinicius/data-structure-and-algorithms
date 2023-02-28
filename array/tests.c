#include "array.h"
#include "assert.h"
#include "stdio.h"
#include "_utils_/conversions.h"
#include "_utils_/asserts.h"
#include "_utils_/data.h"

int main() {

    { // creating
        struct Array* array = create_array(sizeof(int*));
        assert(array->index == 0);
        assert(array->array_item_size == sizeof(int*));
    }

    { // pushing
        struct Array* array = create_array(sizeof(int*));
        array_push(array, intp(1));
        array_push(array, intp(2));
        assert(array->index == 2);
        assert(*array_at(array, 0, int*) == 1);
        assert(*array_at(array, 1, int*) == 2);
        assert(array_at(array, 2, int*) == NULL);
        assert(array_size(array) == 2);
        array_push(array, intp(3));
        assert(array_size(array) == 3);
    }

    { // removing
        struct Array* array = create_array(sizeof(int*));
        array_push(array, intp(1));
        array_push(array, intp(2));
        array_push(array, intp(3));
        assert_array(unpointer_ints(array_to_c_array(array, int*), 3), mksa(1,2,3), 3);
        array_remove_at(array, 1);
        assert_array(unpointer_ints(array_to_c_array(array, int*), 2), mksa(1, 3), 2);
        assert(array_size(array) == 2);
        array_remove_at(array, 0);
        assert_array(unpointer_ints(array_to_c_array(array, int*), 1), mksa(3), 1);
        assert(array_size(array) == 1);
    }

    return 0;
}