#include "stdlib.h"
#include "stdio.h"

struct ArrayItem {
    void* value;
};

struct Array {
    struct ArrayItem** items;
    int index;
    size_t array_item_size;
};

struct ArrayItem* _create_array_item(struct Array* array, void* value) {
    struct ArrayItem* item = (struct ArrayItem*) malloc(sizeof(struct ArrayItem*));
    item->value = value;
    return item;
}

struct Array* create_array(size_t array_item_size) {
    struct Array* array = (struct Array*) malloc(sizeof(struct Array*));
    array->index = 0;
    array->array_item_size = array_item_size;
    return array;
}

#define array_push(array, value) __array_push((array), (void*) value)

void __array_push(struct Array* array, void* value) {
    array->items = (struct ArrayItem**) realloc(array->items, (array->index + 1) * array->array_item_size);
    array->items[array->index] = _create_array_item(array, value);
    array->index++;
}

#define array_at(array, index, type) ({ \
    void* value = __array_at(array, index); \
    (type) value; \
})

void* __array_at(struct Array* array, int index) {
    if (index >= array->index) return NULL;
    return array->items[index]->value;
}

int array_size(struct Array* array) { return array->index; }

#define array_to_c_array(array, type) ({ \
    void** value = __array_to_c_array(array); \
    (type*) value; \
})

void** __array_to_c_array(struct Array* array) {
    void** result = malloc(array_size(array) * array->array_item_size);
    for (int i = 0; i < array_size(array); i++) {
        result[i] = array->items[i]->value;
    }
    return result;
}

void array_remove_at(struct Array* array, int index) {
    for (int i = index + 1; i < array_size(array); i++) 
        array->items[i - 1] = array->items[i];
    array->index--;
}
