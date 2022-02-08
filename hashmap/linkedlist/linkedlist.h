#include <stdlib.h>
#include <stdio.h>

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
