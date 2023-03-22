#include "stdio.h"
#include "assert.h"
#include "heap.h"
#include "_utils_/asserts.h"
#include "_utils_/data.h"
#include "_utils_/conversions.h"
#include "_utils_/comparators.h"

void max_heap_tests() {
    { // creating
        struct Heap* heap = create_max_heap(10);
        assert(heap->max_size == 10);
        assert(heap->current_index == 1);
    }

    { // inserting
        struct Heap* heap = create_max_heap(10);
        heap_insert(heap, intp(5));
        assert(*((int*) heap->elements[1]->value) == 5);
        assert(heap->current_index == 2);
        heap_insert(heap, intp(7));
        assert_array_cmp(heap_to_c_array(heap), mksap(7, 5), 2, intp_equals_intp);
        heap_insert(heap, intp(40));
        assert_array_cmp(heap_to_c_array(heap), mksap(40, 5, 7), 3, intp_equals_intp);
    }

    { // top
        struct Heap* heap = create_max_heap(100);
        for (int i = 100; i >= 1; i--) heap_insert(heap, intp(i));
        assert(*((int*)heap_top(heap)) == 100);
    }

    { // deleting
        struct Heap* heap = create_max_heap(10);
        int values[7] = {5, 15, 10, 30, 35, 40, 25};
        for (int i = 0; i < 7; i++) heap_insert(heap, intp(values[i]));
        assert(*(int*) heap_delete(heap) == 40);
        assert_array_cmp(heap_to_c_array(heap), mksap(35, 30, 25, 5, 15, 10), 6, intp_equals_intp);
        assert(*(int*) heap_delete(heap) == 35);
        assert_array_cmp(heap_to_c_array(heap), mksap(30, 15, 25, 5, 10), 5, intp_equals_intp);
        assert(*(int*) heap_delete(heap) == 30);
        assert_array_cmp(heap_to_c_array(heap), mksap(25, 15, 10, 5), 4, intp_equals_intp);
        assert(*(int*) heap_delete(heap) == 25);
        assert(*(int*) heap_delete(heap) == 15);
        assert(*(int*) heap_delete(heap) == 10);
        assert(*(int*) heap_delete(heap) == 5);   
        heap_insert(heap, intp(70));
        heap_insert(heap, intp(81));
        heap_insert(heap, intp(40));
        assert(*(int*) heap_delete(heap) == 81);   
        assert(*(int*) heap_delete(heap) == 70);   
        assert(*(int*) heap_delete(heap) == 40);   
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
        heap_insert(heap, intp(5));
        assert(*((int*) heap->elements[1]->value) == 5);
        assert(heap->current_index == 2);
        heap_insert(heap, intp(7));
        assert_array_cmp(heap_to_c_array(heap), mksap(5, 7), 2, intp_equals_intp);
        heap_insert(heap, intp(40));
        assert_array_cmp(heap_to_c_array(heap), mksap(5, 7, 40), 3, intp_equals_intp);
    }

    { // top
        struct Heap* heap = create_min_heap(100);
        for (int i = 100; i >= 1; i--) heap_insert(heap, intp(i));
        assert(*((int*) heap_top(heap)) == 1);
    }

    { // deleting
        struct Heap* heap = create_min_heap(10);
        int* values = mksa(5, 15, 10, 30, 35, 40, 25);
        for (int i = 0; i < 7; i++) heap_insert(heap, intp(values[i]));
        assert(*(int*) heap_delete(heap) == 5);
        assert_array_cmp(heap_to_c_array(heap), mksap(10, 15, 25, 30, 35, 40), 6, intp_equals_intp);
        assert(*(int*) heap_delete(heap) == 10);
        assert_array_cmp(heap_to_c_array(heap), mksap(15, 30, 25, 40, 35), 5, intp_equals_intp);
        assert(*(int*) heap_delete(heap) == 15);
        assert_array_cmp(heap_to_c_array(heap), mksap(25, 30, 35, 40), 4, intp_equals_intp);
        assert(*(int*) heap_delete(heap) == 25);
        assert(*(int*) heap_delete(heap) == 30);
        assert(*(int*) heap_delete(heap) == 35);
        assert(*(int*) heap_delete(heap) == 40);   
        heap_insert(heap, intp(70));
        heap_insert(heap, intp(81));
        heap_insert(heap, intp(40));
        assert(*(int*) heap_delete(heap) == 40);   
        assert(*(int*) heap_delete(heap) == 70);   
        assert(*(int*) heap_delete(heap) == 81);   
    }
}

int main() {
    max_heap_tests();
    min_heap_tests();
    return 0;
}