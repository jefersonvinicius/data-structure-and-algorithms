#include "stdlib.h"

struct Heap {
    int* elements;
    int max_size, current_index, size;
};

/*
    node index: i
    left child: 2 * i
    right child: 2 * i + 1

*/


int _parent_index(int i) { return i / 2; }

struct Heap* create_heap(int size) {
    struct Heap* heap = (struct Heap*) malloc(sizeof(struct Heap*));
    heap->max_size = size;
    heap->current_index = 1;
    heap->elements = (int*) malloc(sizeof(int) * size + sizeof(int));
    heap->elements[0] = 0;
    return heap;
}

void heap_insert(struct Heap* heap, int value) {
    int index = heap->current_index;
    while (index > 1 && value > heap->elements[_parent_index(index)]) {
        heap->elements[index] = heap->elements[_parent_index(index)];
        index = _parent_index(index);
    }
    heap->elements[index] = value;
    heap->current_index++;
}

int heap_top(struct Heap* heap) {
    return heap->elements[1];
}
