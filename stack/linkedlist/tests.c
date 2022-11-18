#include "assert.h"
#include "stack.h"

int main() {

    { // should push on the stack
        struct LklStack* stack = create_lklstack();
        lkls_push(stack, 2);
        lkls_push(stack, 3);
        assert(stack->root->data == 3);
        assert(stack->root->next->data == 2);
        assert(stack->root->next->next == NULL);
    }

    { // should determine if is empty
        struct LklStack* stack = create_lklstack();
        assert(lkls_is_empty(stack) == 1);
        lkls_push(stack, 3);
        assert(lkls_is_empty(stack) == 0);
    }

    { // should pop the stack top
        struct LklStack* stack = create_lklstack();
        lkls_push(stack, 2);
        lkls_push(stack, 3);
        lkls_push(stack, 4);
        assert(lkls_pop(stack) == 4);
        assert(lkls_pop(stack) == 3);
        assert(lkls_pop(stack) == 2);
    }

    { // should pop the stack top
        struct LklStack* stack = create_lklstack();
        lkls_push(stack, 2);
        lkls_push(stack, 3);
        lkls_push(stack, 4);
        assert(lkls_top(stack) == 4);
        lkls_pop(stack);
        assert(lkls_top(stack) == 3);
        lkls_pop(stack);
        assert(lkls_top(stack) == 2);
    }

    return 0;
}