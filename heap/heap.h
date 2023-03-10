#include "stdlib.h"
#include "stdio.h"


struct HeapElement {
    void* value;
};

struct Heap {
    struct HeapElement** elements;
    int max_size, current_index, size;
    size_t element_size;
    int (*cmp)(void*, void*);
};

#define HEAP_ROOT_INDEX 1

int _parent_index(int i) { return i / 2; }
int _left_child_index(int i) { return 2 * i; }
int _right_child_index(int i) { return 2 * i + 1; }

int _get_next_child_index(struct Heap* heap, int index) {
    void* current = heap->elements[index];
    int right_child_index = _right_child_index(index);
    int left_child_index = _left_child_index(index);
    int is_valid_right_child_index = right_child_index <= heap->current_index;
    int is_valid_left_child_index = left_child_index <= heap->current_index;
    if (
        is_valid_right_child_index && 
        heap->cmp(heap->elements[right_child_index], current)  && 
        (!is_valid_left_child_index || (is_valid_left_child_index && heap->cmp(heap->elements[right_child_index], heap->elements[left_child_index])))
    ) 
        return right_child_index;
    if (is_valid_left_child_index && heap->cmp(heap->elements[left_child_index], current)) return left_child_index;
    return -1;
}

void _swap_elements(struct HeapElement** elements, int index_a, int index_b) {
    void* tmp = elements[index_a];
    elements[index_a] = elements[index_b];
    elements[index_b] = tmp;
}


int _max_cmp(int* a, int* b) { return *a > *b; }
int _min_cmp(int* a, int* b) { return *a < *b; }

struct HeapElement* __create_heap_element(void* value) {
    struct HeapElement* element = (struct HeapElement*) malloc(sizeof(struct HeapElement));
    element->value = value;
    return element;
}

struct Heap* __create_heap(int size, size_t element_size, int (*cmp)(void*, void*)) {
    struct Heap* heap = (struct Heap*) malloc(sizeof(struct Heap));
    heap->max_size = size;
    heap->current_index = 1;
    heap->element_size = element_size;
    printf("element_size: %ld, size: %d\n", element_size, size);
    printf("oi\n");
    heap->elements = (struct HeapElement**) malloc(sizeof(struct HeapElement) * size);
    printf("oi2\n");
    heap->elements[0] = __create_heap_element(NULL);
    printf("oi2.5\n");
    heap->cmp = cmp;
    printf("oi3\n");
    return heap;
}

#define create_heap(size, element_size, cmp) __create_heap(size, element_size, (int(*)(void*, void*))cmp)

void* elements_values(struct Heap* heap) {
    printf("CURREN INDEX: %d\n", heap->current_index);
    void* result = malloc(heap->element_size * heap->current_index);
    for (int i = 1; i < heap->current_index; i++) {
        printf("VALUE: %d\n", *((int*)heap->elements[i]->value));
        result[i] = *heap->elements[i]->value;
    }
    printf("HE\n");
    return result;
}

struct Heap* create_max_heap(int size) {
    printf("HELLO1\n");
    return create_heap(size, sizeof(int*), _max_cmp);
}

struct Heap* create_min_heap(int size) {
    return create_heap(size, sizeof(int*), _min_cmp);
}

#define heap_insert(heap, value) __heap_insert(heap, (void*) value)

void __heap_insert(struct Heap* heap, void* value) {
    printf("INSERTING: %d\n", *((int*)value));
    int index = heap->current_index;
    while (index > 1 &&  heap->cmp(value, heap->elements[_parent_index(index)])) {
        printf("INDEX: %d\n", index);
        heap->elements[index] = heap->elements[_parent_index(index)];
        index = _parent_index(index);
    }
    heap->elements[index] = __create_heap_element(value);
    heap->current_index++;
    printf("INSERTED\n");
}


#define heap_top(heap, type) ({ \
    void* top = __heap_top(heap); \
    (type) top; \
})

void* __heap_top(struct Heap* heap) {
    if (heap->current_index <= 1) {
        fprintf(stderr, "Heap empty error!\n");
        exit(-1);
    };
    return heap->elements[HEAP_ROOT_INDEX];
}

#define heap_delete(heap, type) ({ \
    void* deleted = __heap_delete(heap); \
    (type) deleted; \
})

void* __heap_delete(struct Heap* heap) {
    void* deleted_value = heap_top(heap, void*);
    void* last = heap->elements[--heap->current_index];
    heap->elements[HEAP_ROOT_INDEX] = last;
    int index = HEAP_ROOT_INDEX;
    while (1) {
        int next_index = _get_next_child_index(heap, index);
        if (next_index == -1) break;
        _swap_elements(heap->elements, index, next_index);
        index = next_index;
    }
    return deleted_value;
}
