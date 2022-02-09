#include <assert.h>

#include "linkedlist.h"

int main() {

    { // should find node by value at linked list
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1, "any"));
        append(linked_list, create_node(2, "any"));
        append(linked_list, create_node(3, "any"));
        assert(find_by_value(linked_list, 1)->value == 1);
        assert(find_by_value(linked_list, 2)->value == 2);
        assert(find_by_value(linked_list, 3)->value == 3);
        assert(find_by_value(linked_list, 4) == NULL);
    }

    { // should find node by key at linked list
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1, "key-1"));
        append(linked_list, create_node(2, "key-2"));
        append(linked_list, create_node(3, "key-3"));
        assert(find_by_key(linked_list, "key-1")->value == 1);
        assert(find_by_key(linked_list, "key-2")->value == 2);
        assert(find_by_key(linked_list, "key-3")->value == 3);
        assert(find_by_key(linked_list, "key-4") == NULL);
    }

     { // should remove node by key
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1, "key-1"));
        append(linked_list, create_node(2, "key-2"));
        append(linked_list, create_node(3, "key-3"));
        append(linked_list, create_node(4, "key-4"));
        delete_by_key(linked_list, "key-2");
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 3);
        assert(linked_list->head->next->next->value == 4);
        assert(linked_list->head->next->next->next == NULL);
        delete_by_key(linked_list, "key-1");
        assert(linked_list->head->value == 3);
        assert(linked_list->head->next->value == 4);
        assert(linked_list->head->next->next == NULL);
        delete_by_key(linked_list, "key-4");
        assert(linked_list->head->value == 3);
        assert(linked_list->head->next == NULL);
    }

    return 0;
}