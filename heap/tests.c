#include "stdio.h"
#include "assert.h"
#include "heap.h"
#include "../_utils_/asserts.h"

int main() {

    { // creating
        struct Heap* heap = create_heap(10);
        assert(heap->max_size == 10);
        assert(heap->current_index == 1);
    }

    { // inserting
        struct Heap* heap = create_heap(10);
        heap_insert(heap, 5);
        assert(heap->elements[1] == 5);
        assert(heap->current_index == 2);
        heap_insert(heap, 7);
        int expected[3] = {0, 7, 5};
        assert_array(heap->elements, expected, 3);
        heap_insert(heap, 40);
        int expected2[4] = {0, 40, 5, 7};
        assert_array(heap->elements, expected2, 4);
    }

    { // top
        struct Heap* heap = create_heap(100);
        for (int i = 100; i >= 1; i--) heap_insert(heap, i);
        assert(heap_top(heap) == 100);
    }

    { // deleting
        struct Heap* heap = create_heap(10);
        int values[7] = {5, 15, 10, 30, 35, 40, 25};
        for (int i = 0; i < 7; i++) heap_insert(heap, values[i]);
        assert(heap_delete(heap) == 40);
        int expected[7] = {0, 35, 30, 25, 5, 15, 10};
        assert_array(heap->elements, expected, 7);
        assert(heap_delete(heap) == 35);
        int expected2[7] = {0, 30, 15, 25, 5, 10};
        assert_array(heap->elements, expected2, 6);
        assert(heap_delete(heap) == 30);
        int expected3[7] = {0, 25, 15, 10, 5};
        assert_array(heap->elements, expected3, 5);
        assert(heap_delete(heap) == 25);
        assert(heap_delete(heap) == 15);
        assert(heap_delete(heap) == 10);
        assert(heap_delete(heap) == 5);   
        heap_insert(heap, 70);
        heap_insert(heap, 81);
        heap_insert(heap, 40);
        assert(heap_delete(heap) == 81);   
        assert(heap_delete(heap) == 70);   
        assert(heap_delete(heap) == 40);   
    }

    { // min heap
        
    }

    return 0;
}