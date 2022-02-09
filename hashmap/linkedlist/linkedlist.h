#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node {
    int value;
    char* key;
    struct Node *next; 
};

struct LinkedList {
    struct Node *head;
};

struct Node* create_node(int value, char* key) {
    struct Node* node = malloc(sizeof(struct Node));
    node->value = value;
    node->key = key;
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

struct Node* find_by_value(struct LinkedList* linked_list, int value) {
    struct Node* node = linked_list->head;
    while (node != NULL) {
        if (node->value == value) return node;
        node = node->next;
    }
    return NULL;
}

struct Node* find_by_key(struct LinkedList* linked_list, char* key) {
    struct Node* node = linked_list->head;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) return node;
        node = node->next;
    }
    return NULL;
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

void delete_by_key(struct LinkedList* linked_list, char* key) {
    if (strcmp(linked_list->head->key, key) == 0) {
        linked_list->head = linked_list->head->next;
        return;
    }

    struct Node* node = malloc(sizeof(struct Node));
    node = linked_list->head;

    while (node->next != NULL) {
        if (strcmp(node->next->key, key) == 0) {
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
