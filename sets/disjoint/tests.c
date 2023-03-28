#include "disjoint.h"
#include "assert.h"
#include "_utils_/asserts.h"

int main() {
    { // creating
        struct IntDisjointSet* set = create_int_disjoint_set();
        int expected[MAX_DISJOINT_SET]; for (int i = 0; i < MAX_DISJOINT_SET; i++) expected[i] = i;
        assert_array(set->parent, expected, MAX_DISJOINT_SET);
    }

    { // find
        struct IntDisjointSet* set = create_int_disjoint_set(); 
        assert(int_disjoint_set_find(set, 0) == 0);
        assert(int_disjoint_set_find(set, 1) == 1);
        assert(int_disjoint_set_find(set, 2) == 2);
    }
 
    { // union
        struct IntDisjointSet* set = create_int_disjoint_set(); 
        int_disjoint_set_union(set, 0, 1);
        assert(int_disjoint_set_find(set, 0) == 0);
        assert(int_disjoint_set_find(set, 1) == 0);
        int_disjoint_set_union(set, 2, 0);
        assert(int_disjoint_set_find(set, 0) == 2);
        assert(int_disjoint_set_find(set, 1) == 2);
        assert(int_disjoint_set_find(set, 2) == 2);
    }

    { // has
        struct IntDisjointSet* set = create_int_disjoint_set(); 
        assert(int_disjoint_set_has(set, 0, 1) == 0);
        assert(int_disjoint_set_has(set, 1, 2) == 0);
        assert(int_disjoint_set_has(set, 2, 3) == 0);
        assert(int_disjoint_set_has(set, 3, 4) == 0);
        int_disjoint_set_union(set, 0, 1);
        assert(int_disjoint_set_has(set, 0, 1) == 1);
        assert(int_disjoint_set_has(set, 1, 2) == 0);
        assert(int_disjoint_set_has(set, 2, 3) == 0);
        assert(int_disjoint_set_has(set, 3, 4) == 0);
        int_disjoint_set_union(set, 3, 4);
        assert(int_disjoint_set_has(set, 0, 1) == 1);
        assert(int_disjoint_set_has(set, 1, 2) == 0);
        assert(int_disjoint_set_has(set, 2, 3) == 0);
        assert(int_disjoint_set_has(set, 3, 4) == 1);
        int_disjoint_set_union(set, 2, 3);
        int_disjoint_set_union(set, 0, 2);
        assert(int_disjoint_set_has(set, 0, 1) == 1);
        assert(int_disjoint_set_has(set, 1, 2) == 1);
        assert(int_disjoint_set_has(set, 2, 3) == 1);
        assert(int_disjoint_set_has(set, 3, 4) == 1);
        assert(int_disjoint_set_has(set, 1, 3) == 1);
        assert(int_disjoint_set_has(set, 1, 5) == 0);
        int_disjoint_set_union(set, 0, 5);
        assert(int_disjoint_set_has(set, 5, 0) == 1);
        assert(int_disjoint_set_has(set, 5, 1) == 1);
        assert(int_disjoint_set_has(set, 5, 2) == 1);
        assert(int_disjoint_set_has(set, 5, 3) == 1);
        assert(int_disjoint_set_has(set, 5, 4) == 1);
    }

    return 0;
}