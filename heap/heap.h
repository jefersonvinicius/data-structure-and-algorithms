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

#define HEAP_ROOT_INDEX 1

int _parent_index(int i) { return i / 2; }
int _left_child_index(int i) { return 2 * i; }
int _right_child_index(int i) { return 2 * i + 1; }

int _get_next_child_index(struct Heap* heap, int index) {
    int current = heap->elements[index];
    int right_child_index = _right_child_index(index);
    if (right_child_index <= heap->current_index && current < heap->elements[right_child_index]) return right_child_index;
    int left_child_index = _left_child_index(index);
    if (left_child_index <= heap->current_index && current < heap->elements[left_child_index]) return left_child_index;
    return -1;
}

void _swap_elements(int* elements, int index_a, int index_b) {
    int tmp = elements[index_a];
    elements[index_a] = elements[index_b];
    elements[index_b] = tmp;
}

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
    return heap->elements[HEAP_ROOT_INDEX];
}

int heap_delete(struct Heap* heap) {
    int deleted_value = heap_top(heap);
    printf("DELETING: %d\n", deleted_value);
    int last = heap->elements[--heap->current_index];
    heap->elements[HEAP_ROOT_INDEX] = last;
    int index = HEAP_ROOT_INDEX;
    while (1) {
        int next_index = _get_next_child_index(heap, index);
        if (next_index == -1) break;
        printf("MOVING %d to %d\n", heap->elements[index], heap->elements[next_index]);
        _swap_elements(heap->elements, index, next_index);
        index = next_index;
    }
    printf("DELETED: %d\n", deleted_value);
    return deleted_value;
}
