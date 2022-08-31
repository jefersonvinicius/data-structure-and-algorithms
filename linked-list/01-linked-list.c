#include <assert.h>
#include "linkedlist.h"

int main() {
    { // should create linked list correctly
        struct LinkedList* linked_list = create_linked_list();
        assert(is_empty(linked_list) == 1);
        assert(size(linked_list) == 0);
        assert(linked_list->head == NULL);
    }

    { // should push node to linked list correctly
        struct LinkedList* linked_list = create_linked_list();
        push(linked_list, create_node(1));
        assert(is_empty(linked_list) == 0);
        assert(size(linked_list) == 1);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next == NULL);
        push(linked_list, create_node(2));
        assert(linked_list->head->value == 2);
        assert(linked_list->head->next->value == 1);
        append(linked_list, create_node(3));
        assert(linked_list->head->value == 2);
        assert(linked_list->head->next->value == 1);
        assert(linked_list->head->next->next->value == 3);
    }

    { // should append node to linked list head correctly
        struct LinkedList* linked_list = create_linked_list();
        struct Node* node = create_node(1);
        append(linked_list, node);
        assert(is_empty(linked_list) == 0);
        assert(size(linked_list) == 1);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next == NULL);
    }

    { // should bind node to next node available
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1));
        append(linked_list, create_node(2));
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 2);
    }

    { // should delete by value correctly even when value is in start
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1));
        append(linked_list, create_node(2));
        append(linked_list, create_node(3));
        delete_by_value(linked_list, 1);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 2);
        assert(linked_list->head->next->value == 3);
    }

    { // should delete by value correctly when value is in middle
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1));
        append(linked_list, create_node(2));
        append(linked_list, create_node(3));
        delete_by_value(linked_list, 2);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 3);
    }

    { // should delete by value correctly when value is in the end
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1));
        append(linked_list, create_node(2));
        append(linked_list, create_node(3));
        delete_by_value(linked_list, 3);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 2);
    }

    { // should delete by reference correctly even when value is in start
        struct LinkedList* linked_list = create_linked_list();
        struct Node* node = create_node(1);
        append(linked_list, node);
        append(linked_list, create_node(2));
        append(linked_list, create_node(3));
        delete_by_reference(linked_list, node);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 2);
        assert(linked_list->head->next->value == 3);
    }

    { // should delete by reference correctly when value is in middle
        struct LinkedList* linked_list = create_linked_list();
        struct Node* node = create_node(2);
        append(linked_list, create_node(1));
        append(linked_list, node);
        append(linked_list, create_node(3));
        delete_by_reference(linked_list, node);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 3);
    }

    { // should delete by reference correctly when value is in the end
        struct LinkedList* linked_list = create_linked_list();
        struct Node* node = create_node(3);
        append(linked_list, create_node(1));
        append(linked_list, create_node(2));
        append(linked_list, node);
        delete_by_reference(linked_list, node);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 2);
    }

    { // should get node at index
        struct LinkedList* linked_list = create_linked_list();
        append(linked_list, create_node(1));
        append(linked_list, create_node(2));
        append(linked_list, create_node(3));
        struct Node* node = get_at(linked_list, 1);
        struct Node* node_not_found = get_at(linked_list, 3);
        assert(node->value == 2);
        assert(node_not_found == NULL);
    }

    { // should insert node after another node
        struct LinkedList* linked_list = create_linked_list();
        struct Node* node_ref = create_node(2);
        append(linked_list, create_node(1));
        append(linked_list, node_ref);
        append(linked_list, create_node(4));
        insert_after_node(node_ref, create_node(3));
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 2);
        assert(linked_list->head->next->next->value == 3);
        assert(linked_list->head->next->next->next->value == 4);
    }

    return 0;
}