#include "stdlib.h"

struct Heap {
    int* elements;
    int max_size, current_index, size;
    int (*cmp)(int, int);
};

/*
    node index: i
    left child: 2 * i
    right child: 2 * i + 1

*/

#define HEAP_ROOT_INDEX 1

int _parent_index(int i) { return i / 2; }
int _left_child_index(int i) { return 2 * i; }
int _right_child_index(int i) { return 2 * i + 1; }

int _get_next_child_index(struct Heap* heap, int index) {
    int current = heap->elements[index];
    int right_child_index = _right_child_index(index);
    int left_child_index = _left_child_index(index);
    int is_valid_right_child_index = right_child_index <= heap->current_index;
    int is_valid_left_child_index = left_child_index <= heap->current_index;
    if (
        is_valid_right_child_index && 
        heap->cmp(heap->elements[right_child_index], current)  && 
        (!is_valid_left_child_index || (is_valid_left_child_index && heap->elements[right_child_index] >= heap->elements[left_child_index]))
    ) 
        return right_child_index;
    if (is_valid_left_child_index && heap->cmp(heap->elements[left_child_index], current)) return left_child_index;
    return -1;
}

void _swap_elements(int* elements, int index_a, int index_b) {
    int tmp = elements[index_a];
    elements[index_a] = elements[index_b];
    elements[index_b] = tmp;
}


int max_cmp(int a, int b) {
    return a > b;
}

struct Heap* create_heap(int size, int (*cmp)(int, int)) {
    struct Heap* heap = (struct Heap*) malloc(sizeof(struct Heap*));
    heap->max_size = size;
    heap->current_index = 1;
    heap->elements = (int*) malloc(sizeof(int) * size + sizeof(int));
    heap->elements[0] = 0;
    heap->cmp = cmp;
    return heap;
}

void heap_insert(struct Heap* heap, int value) {
    int index = heap->current_index;
    while (index > 1 &&  heap->cmp(value, heap->elements[_parent_index(index)])) {
        heap->elements[index] = heap->elements[_parent_index(index)];
        index = _parent_index(index);
    }
    heap->elements[index] = value;
    heap->current_index++;
}


int heap_top(struct Heap* heap) {
    if (heap->current_index <= 1) {
        fprintf(stderr, "Heap empty error!\n");
        exit(-1);
    };
    return heap->elements[HEAP_ROOT_INDEX];
}

int heap_delete(struct Heap* heap) {
    int deleted_value = heap_top(heap);
    int last = heap->elements[--heap->current_index];
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
