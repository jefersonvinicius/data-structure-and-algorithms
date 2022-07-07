#include <stdio.h>
#include <assert.h>
#include "charstack.h"

int main() {

    { // should push node
        struct StackNode* stack = NULL;
        assert(is_empty(stack) == 1);
        push(&stack, 'a');
        assert(is_empty(stack) == 0);
    }

    { // should get top element
        struct StackNode* stack = NULL;
        assert(top(stack) == NULL);
        push(&stack, 'a');
        push(&stack, 'b');
        assert(*top(stack) == 'b');
    }

    { // should pop top element
        struct StackNode* stack = NULL;
        push(&stack, 'a');
        push(&stack, 'b');
        pop(&stack);
        assert(*top(stack) == 'a');
        push(&stack, 'c');
        assert(*top(stack) == 'c');
        pop(&stack);
        pop(&stack);
        assert(top(stack) == NULL);
    }
    

    return 0;
}