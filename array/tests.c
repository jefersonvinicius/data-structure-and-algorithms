#include "array.h"
#include "assert.h"
#include "stdio.h"
#include "_utils_/conversions.h"

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
        
    }

    return 0;
}