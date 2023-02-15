#include "stdlib.h"

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
    item->value = malloc(array->array_item_size);
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
    return array->items[index]->value;
}

