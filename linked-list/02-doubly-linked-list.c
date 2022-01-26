#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

struct DoublyLinkedList {
    struct Node* head;
};

struct DoublyLinkedList* create_list() {
    struct DoublyLinkedList* list = malloc(sizeof(struct DoublyLinkedList));
    list->head = NULL;
    return list;
}

void *mallocNode() {
    return malloc(sizeof(struct Node));
}

struct Node* create_node(int value) {
    struct Node* node = mallocNode();
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void append(struct DoublyLinkedList* list, struct Node* node) {
    if (list->head == NULL) {
        node->prev = NULL;
        node->next = NULL;
        list->head = node;
        return;
    }

    struct Node* last_node = malloc(sizeof(struct Node));
    last_node = list->head;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }

    node->next = NULL;
    node->prev = last_node;
    last_node->next = node;
}

void push(struct DoublyLinkedList* list, struct Node* node) {
    if (list->head == NULL) {
        node->prev = NULL;
        node->next = NULL;
        list->head = node;
        return;
    }
    struct Node* tmp_node = mallocNode();
    tmp_node = list->head;
    tmp_node->prev = node;
    node->prev = NULL;
    node->next = tmp_node;
    list->head = node;
}

void insert_after(struct Node* prev_node, struct Node* node) {

    if (prev_node->next == NULL) {
        node->next = NULL;
        prev_node->next = node;
        node->prev = prev_node;
        return;
    }

    prev_node->next->prev = node;
    node->next = prev_node->next;
    prev_node->next = node;
    node->prev = prev_node;
}

void clear_list(struct DoublyLinkedList* list) {
    struct Node* current = list->head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

void delete_node(struct Node* node) {
    if (node->prev == NULL) {
        struct Node* next = node->next;
        next->prev = NULL;   
        *node = *next;
        return;
    }

    if (node->next == NULL) {
        node->prev->next = NULL;
        free(node);
        return;
    }

    struct Node* next = node->next;
    next->prev = node->prev;
    *node = *next;
}

void print_list(struct DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("List empty\n");
        return;
    }

    printf("Next order:\n");
    struct Node* node = list->head;
    while (node->next != NULL) {
        printf("%d -> ", node->value);
        node = node->next;
    }
    printf("%d\n", node->value);

    printf("Prev order:\n");
    while (node != NULL) {
        if (node->prev == NULL) {
            printf("%d\n", node->value);
        } else {    
            printf("%d -> ", node->value);
        }
        node = node->prev;
    }
}

int main() {
    { // should create doubly linked list
        struct DoublyLinkedList* list = create_list();
        assert(list != NULL);
        assert(list->head == NULL);
    }

    { // should create a node
        struct Node* node = create_node(1);
        assert(node->value == 1);
        assert(node->next == NULL);
        assert(node->prev == NULL);
    }

    { // should append node at linked list
        struct DoublyLinkedList* list = create_list();
        append(list, create_node(1));
        append(list, create_node(2));
        append(list, create_node(3));
        assert(list->head->value == 1);
        assert(list->head->next->value == 2);
        assert(list->head->next->next->value == 3);
        assert(list->head->next->next->prev->value == 2);
        assert(list->head->next->next->prev->prev->value == 1);
        assert(list->head->next->next->prev->prev->prev == NULL);
    }

    { // should push node at linked list
        struct DoublyLinkedList* list = create_list();
        push(list, create_node(1));
        push(list, create_node(2));
        push(list, create_node(3));
        assert(list->head->value == 3);
        assert(list->head->next->value == 2);
        assert(list->head->next->next->value == 1);
        assert(list->head->next->next->prev->value == 2);
        assert(list->head->next->next->prev->prev->value == 3);
        assert(list->head->next->next->prev->prev->prev == NULL);
    }

    { // should insert node after another node in start
        struct DoublyLinkedList* list = create_list();
        struct Node* node1 = create_node(1); 
        struct Node* node2 = create_node(2); 
        append(list, node1);
        append(list, node2);

        insert_after(node1, create_node(4));
        
        assert(list->head->value == 1);
        assert(list->head->next->value == 4);
        assert(list->head->next->next->value == 2);
        assert(list->head->next->next->prev->value == 4);
        assert(list->head->next->next->prev->prev->value == 1);
        assert(list->head->next->next->prev->prev->prev == NULL);
    }

    { // should insert node after another node in end
        struct DoublyLinkedList* list = create_list();
        struct Node* node1 = create_node(1); 
        struct Node* node2 = create_node(2); 
        append(list, node1);
        append(list, node2);

        insert_after(node2, create_node(4));

        assert(list->head->value == 1);
        assert(list->head->next->value == 2);
        assert(list->head->next->next->value == 4);
        assert(list->head->next->next->prev->value == 2);
        assert(list->head->next->next->prev->prev->value == 1);
        assert(list->head->next->next->prev->prev->prev == NULL);
    }

    { // should insert node after another node in middle
        struct DoublyLinkedList* list = create_list();
        struct Node* node2 = create_node(2); 
        append(list, create_node(1));
        append(list, node2);
        append(list, create_node(3));

        insert_after(node2, create_node(4));

        assert(list->head->value == 1);
        assert(list->head->next->value == 2);
        assert(list->head->next->next->value == 4);
        assert(list->head->next->next->next->value == 3);
        assert(list->head->next->next->next->prev->value == 4);
        assert(list->head->next->next->next->prev->prev->value == 2);
        assert(list->head->next->next->next->prev->prev->prev->value == 1);
        assert(list->head->next->next->next->prev->prev->prev->prev == NULL);
    }

    { // should delete node in start
        struct DoublyLinkedList* list = create_list();
        struct Node* node1 = create_node(1); 
        append(list, node1);
        append(list, create_node(2));
        append(list, create_node(3));

        delete_node(node1);

        assert(list->head->value == 2);
        assert(list->head->next->value == 3);
        assert(list->head->next->next == NULL);
        assert(list->head->next->prev->value == 2);
        assert(list->head->next->prev->prev == NULL);
    }

    { // should delete node in middle
        struct DoublyLinkedList* list = create_list();
        struct Node* node2 = create_node(2); 
        append(list, create_node(1));
        append(list, node2);
        append(list, create_node(3));

        delete_node(node2);
        
        assert(list->head->value == 1);
        assert(list->head->next->value == 3);
        assert(list->head->next->next == NULL);
        assert(list->head->next->prev->value == 1);
        assert(list->head->next->prev->prev == NULL);
    }

    { // should delete node in end
        struct DoublyLinkedList* list = create_list();
        struct Node* node3 = create_node(3); 
        append(list, create_node(1));
        append(list, create_node(2));
        append(list, node3);

        delete_node(node3);
        
        assert(list->head->value == 1);
        assert(list->head->next->value == 2);
        assert(list->head->next->next == NULL);
        assert(list->head->next->prev->value == 1);
        assert(list->head->next->prev->prev == NULL);
    }

    return 0;
}

