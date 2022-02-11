#include <assert.h>
#include <string.h>
#include "node.h"

int main() {

    { // should create the node correctly
        struct Node* node = create_node("jeferson", 1);
        assert(strcmp(node->key, "jeferson") == 0);
        assert(node->value == 1);
    }

    return 0;
}