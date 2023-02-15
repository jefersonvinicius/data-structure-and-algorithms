#include "array.h"
#include "assert.h"

int main() {

    { // creating
        struct Array* array = create_array(sizeof(int));
        assert(array->index == 0);
        assert(array->array_item_size == sizeof(int));
    }

    { // pushing
        struct Array* array = create_array(5);
        array_push(array, 1);
        array_push(array, 2);
        assert(array->index == 2);
        assert(array_at(array, 0, int) == 1);
        // assert(array_at(array, 1) == 1);
    }

    return 0;
}