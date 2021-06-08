#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next; 
};

struct Queue {
    struct Node *front, *rear;
};

struct Node* create_node(int value) {
    struct Node *node = malloc(sizeof(struct Node));
    node->data = value;
    node->next = NULL;
    return node;
};

struct Queue* create_queue() {
    struct Queue *queue = malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
};

int queue_is_empty(struct Queue* queue) {
    return queue->front == NULL;
}

void enqueue(struct Queue *queue, int value) {
    struct Node* new_node = create_node(value);
    if (queue_is_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

void dequeue(struct Queue *queue) {
    if (queue_is_empty(queue)) {
        printf("Error on dequeue: queue is empty");
        exit(EXIT_SUCCESS);
    }

    struct Node* tmp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) queue->rear = NULL;

    free(tmp);
}

void dequeue_and_print_all_queue(struct Queue *queue) {
    while (queue->front != NULL) {
        printf("(FRONT %p::%d)", queue->front, queue->front->data);
        if (queue->front->next != NULL) printf(" -> (NEXT %p::%d)", queue->front->next, queue->front->next->data);
        printf("\n");
        dequeue(queue);
    }
}

int main() {

    struct Queue *queue = create_queue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);

    dequeue_and_print_all_queue(queue);
    
    return 0;
}