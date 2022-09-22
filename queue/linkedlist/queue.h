#ifndef __LKL_QUEUE_H__
#define __LKL_QUEUE_H__

#include <stdlib.h>

// Queue Linked List Implementation

struct LklQueueNode {
    int data;
    struct LklQueueNode *next; 
};

struct LklQueue {
    struct LklQueueNode *front;
};

struct LklQueueNode* create_lkl_queue_node(int value) {
    struct LklQueueNode *node = (struct LklQueueNode*) malloc(sizeof(struct LklQueueNode));
    node->data = value;
    node->next = NULL;
    return node;
};

struct LklQueue* create_lkl_queue() {
    struct LklQueue *queue = (struct LklQueue*) malloc(sizeof(struct LklQueue*));
    queue->front = NULL;
    return queue;
};

struct LklQueueNode* __get_last_lkl_queue_node(struct LklQueue* queue) {
    struct LklQueueNode* node = queue->front;
    while (node->next != NULL) node = node->next;
    return node;
}

int lklq_is_empty(struct LklQueue* queue) {
    return queue->front == NULL;
}

void lklq_enqueue(struct LklQueue *queue, int value) {
    struct LklQueueNode* new_node = create_lkl_queue_node(value);
    if (lklq_is_empty(queue)) {
        queue->front = new_node;
    } else {
        __get_last_lkl_queue_node(queue)->next = new_node;
    }
}

void lklq_dequeue(struct LklQueue *queue) {
    if (lklq_is_empty(queue)) return;

    struct LklQueueNode* tmp = queue->front;
    queue->front = queue->front->next;

    free(tmp);
}

#endif