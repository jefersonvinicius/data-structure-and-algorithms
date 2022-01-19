#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct Node {
    int value;
    struct Node *next; 
};

struct LinkedList {
    struct Node *head;
};

struct Node* create_node(int value) {
    struct Node* node = malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    return node;
}

struct LinkedList* create_linked_list() {
    struct LinkedList* linked_list = malloc(sizeof(struct LinkedList));
    linked_list->head = NULL;
    return linked_list;
}

void add_node(struct LinkedList* linked_list, struct Node* node) {
    if (linked_list->head == NULL) {
        linked_list->head = node;
        return;
    }

    struct Node* linked_list_node = malloc(sizeof(struct Node));
    linked_list_node = linked_list->head;
    
    while (1) {
        if (linked_list_node->next == NULL) {
            linked_list_node->next = node;
            break;
        } else {
            linked_list_node = linked_list_node->next;
        }
    }
}

int is_empty(struct LinkedList* linked_list) {
    return linked_list->head == NULL;
}

int size(struct LinkedList* linked_list) {
    if (linked_list->head == NULL) return 0;

    struct Node* node = malloc(sizeof(struct Node));
    node = linked_list->head;
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void delete_by_value(struct LinkedList* linked_list, int value) {
    if (linked_list->head->value == value) {
        linked_list->head = linked_list->head->next;
        return;
    }
}



int main() {
    { // should create linked list correctly
        struct LinkedList* linked_list = create_linked_list();
        assert(is_empty(linked_list) == 1);
        assert(size(linked_list) == 0);
        assert(linked_list->head == NULL);
    }

    { // should add node to linked list head correctly
        struct LinkedList* linked_list = create_linked_list();
        struct Node* node = create_node(1);
        add_node(linked_list, node);
        assert(is_empty(linked_list) == 0);
        assert(size(linked_list) == 1);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next == NULL);
    }

    { // should bind node to next node available
        struct LinkedList* linked_list = create_linked_list();
        add_node(linked_list, create_node(1));
        add_node(linked_list, create_node(2));
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 2);
    }

    { // should delete by value correctly even when value is in start
        struct LinkedList* linked_list = create_linked_list();
        add_node(linked_list, create_node(1));
        add_node(linked_list, create_node(2));
        add_node(linked_list, create_node(3));
        delete_by_value(linked_list, 1);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 2);
        assert(linked_list->head->next->value == 3);
    }

    { // should delete by value correctly when value is not in middle
        struct LinkedList* linked_list = create_linked_list();
        add_node(linked_list, create_node(1));
        add_node(linked_list, create_node(2));
        add_node(linked_list, create_node(3));
        delete_by_value(linked_list, 2);
        assert(size(linked_list) == 2);
        assert(linked_list->head->value == 1);
        assert(linked_list->head->next->value == 2);
    }


    return 0;
}