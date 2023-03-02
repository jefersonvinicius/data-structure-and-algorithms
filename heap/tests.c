#include "stdio.h"
#include "assert.h"
#include "heap.h"
#include "_utils_/asserts.h"
#include "_utils_/data.h"
#include "_utils_/conversions.h"

void max_heap_tests() {
    { // creating
        struct Heap* heap = create_max_heap(10);
        assert(heap->max_size == 10);
        assert(heap->current_index == 1);
    }

    { // inserting
        struct Heap* heap = create_max_heap(10);
        heap_insert(heap, intp(5));
        assert(*((int*) heap->elements[1]) == 5);
        assert(heap->current_index == 2);
        heap_insert(heap, 7);
        assert_array((int*) heap->elements, mksa(0, 7, 5), 3);
        heap_insert(heap, 40);
        assert_array((int*) heap->elements, mksa(0, 40, 5, 7), 4);
    }

    { // top
        struct Heap* heap = create_max_heap(100);
        for (int i = 100; i >= 1; i--) heap_insert(heap, intp(i));
        assert(*heap_top(heap, int*) == 100);
    }

    { // deleting
        struct Heap* heap = create_max_heap(10);
        int values[7] = {5, 15, 10, 30, 35, 40, 25};
        for (int i = 0; i < 7; i++) heap_insert(heap, intp(values[i]));
        assert(*heap_delete(heap, int*) == 40);
        assert_array((int*) heap->elements, mksa(0, 35, 30, 25, 5, 15, 10), 7);
        assert(*heap_delete(heap, int*) == 35);
        assert_array((int*) heap->elements, mksa(0, 30, 15, 25, 5, 10), 6);
        assert(*heap_delete(heap, int*) == 30);
        assert_array((int*) heap->elements, mksa(0, 25, 15, 10, 5), 5);
        assert(*heap_delete(heap, int*) == 25);
        assert(*heap_delete(heap, int*) == 15);
        assert(*heap_delete(heap, int*) == 10);
        assert(*heap_delete(heap, int*) == 5);   
        heap_insert(heap, 70);
        heap_insert(heap, 81);
        heap_insert(heap, 40);
        assert(*heap_delete(heap, int*) == 81);   
        assert(*heap_delete(heap, int*) == 70);   
        assert(*heap_delete(heap, int*) == 40);   
    }
}

void min_heap_tests() {
    { // creating
        struct Heap* heap = create_min_heap(10);
        assert(heap->max_size == 10);
        assert(heap->current_index == 1);
    }

    { // inserting
        struct Heap* heap = create_min_heap(10);
        heap_insert(heap, 5);
        assert(*((int*) heap->elements[1]) == 5);
        assert(heap->current_index == 2);
        heap_insert(heap, 7);
        assert_array((int*) heap->elements, mksa(0, 5, 7), 3);
        heap_insert(heap, 40);
        assert_array((int*) heap->elements, mksa(0, 5, 7, 40), 4);
    }

    { // top
        struct Heap* heap = create_min_heap(100);
        for (int i = 100; i >= 1; i--) heap_insert(heap, intp(i));
        assert(*heap_top(heap, int*) == 1);
    }

    { // deleting
        struct Heap* heap = create_min_heap(10);
        int* values = mksa(5, 15, 10, 30, 35, 40, 25);
        for (int i = 0; i < 7; i++) heap_insert(heap, intp(values[i]));
        assert(*heap_delete(heap, int*) == 5);
        assert_array((int*) heap->elements, mksa(0, 10, 15, 25, 30, 35, 40), 7);
        assert(*heap_delete(heap, int*) == 10);
        assert_array((int*) heap->elements, mksa(0, 15, 30, 25, 40, 35), 6);
        assert(*heap_delete(heap, int*) == 15);
        assert_array((int*) heap->elements, mksa(0, 25, 30, 35, 40), 5);
        assert(*heap_delete(heap, int*) == 25);
        assert(*heap_delete(heap, int*) == 30);
        assert(*heap_delete(heap, int*) == 35);
        assert(*heap_delete(heap, int*) == 40);   
        heap_insert(heap, 70);
        heap_insert(heap, 81);
        heap_insert(heap, 40);
        assert(*heap_delete(heap, int*) == 40);   
        assert(*heap_delete(heap, int*) == 70);   
        assert(*heap_delete(heap, int*) == 81);   
    }
}

int main() {
    max_heap_tests();
    min_heap_tests();
    return 0;
}