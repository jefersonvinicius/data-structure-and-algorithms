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

void append(struct LinkedList* linked_list, struct Node* node) {
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

struct Node* get_at(struct LinkedList* linked_list, int index) {
    struct Node* node = malloc(sizeof(struct Node));
    node = linked_list->head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}

void push(struct LinkedList* linked_list, struct Node* node) {
    if (linked_list->head == NULL) {
        linked_list->head = node;
        return;
    }

    struct Node* head = malloc(sizeof(struct Node)); 
    head = linked_list->head;

    linked_list->head = node;
    node->next = head;
}

void insert_after_node(struct Node* prev_node, struct Node* inserting_node) {
    inserting_node->next = prev_node->next;
    prev_node->next = inserting_node;
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

    struct Node* node = malloc(sizeof(struct Node));
    node = linked_list->head;

    while (node->next != NULL) {
        if (node->next->value == value) {
            node->next = node->next->next;
            break;
        } else {
            node = node->next;
        }
    }
}

void delete_by_reference(struct LinkedList* linked_list, struct Node* node_to_delete) {
    if (linked_list->head == node_to_delete) {
        linked_list->head = linked_list->head->next;
        return;
    }

    struct Node* node = malloc(sizeof(struct Node));
    node = linked_list->head;

    while (node->next != NULL) {
        if (node->next == node_to_delete) {
            node->next = node->next->next;
            break;
        } else {
            node = node->next;
        }
    }
}

void print_lk(struct LinkedList* linked_list) {
    struct Node* node = malloc(sizeof(struct Node));
    node = linked_list->head;
    while (node != NULL) {
        if (node->next == NULL) {
            printf("(%p) %d\n", &node, node->value);
        } else {
            printf("(%p) %d -> ", &node, node->value);
        }
        node = node->next;
    }
}

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