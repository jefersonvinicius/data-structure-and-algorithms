#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue {
    int current_index;
    int max;
    int *data;
};

struct Queue* create_queue(int max) {
    struct Queue* queue = malloc(sizeof(int) + sizeof(int) * max);
    queue->current_index = -1;
    queue->max = max;
    queue->data = malloc(sizeof(int) * max);
    return queue;
}

int is_empty(struct Queue* queue) {
    return queue->current_index == -1;
}

int is_full(struct Queue* queue) {
    return queue->current_index >= queue->max;
}

void enqueue(struct Queue** queue, int value) {
    if (is_full(*queue)) {
        printf("Error on enqueue: queue is full\n");
        exit(EXIT_FAILURE);
    }

    (*queue)->data[++(*queue)->current_index] = value;
}

void dequeue(struct Queue* queue) { 
    if (is_empty(queue)) {
        printf("Error on dequeue: queue is empty\n");
        exit(EXIT_FAILURE);
    }

    int *tmp;
    int current_index_holder = queue->current_index;
    int max_holder = queue->max;

    memcpy(tmp, ++queue->data, sizeof(queue->data)); // copy to tmp variable queue data removing first position
    queue->data = malloc(sizeof(int) * queue->max); // alloc new memory
    memcpy(queue->data, tmp, sizeof(queue->data)); // copy tmp data to queue data memory space
    queue->current_index = current_index_holder - 1; 
    queue->max = max_holder;
}

int front(struct Queue* queue) {
    return queue->data[0];
}

int rear(struct Queue* queue) {
    return queue->data[queue->current_index];
}

int main() {

    struct Queue* queue = create_queue(5);

    enqueue(&queue, 2);
    enqueue(&queue, 9);
    enqueue(&queue, 3);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));

    dequeue(queue);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));

    enqueue(&queue, 10);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));
    
    return 0;
}