#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int *data;
};

struct Queue* create_queue(int capacity) {
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = 0;
    queue->data = malloc(sizeof(int) * capacity);
    return queue;
}

int is_empty(struct Queue* queue) {
    return queue->size == 0;
}

int is_full(struct Queue* queue) {
    return queue->size >= queue->capacity;
}

void enqueue(struct Queue* queue, int value) {
    if (is_full(queue)) {
        printf("Error on enqueue: queue is full\n");
        exit(EXIT_FAILURE);
    }

    queue->data[queue->rear++] = value;
    queue->size++;
}

int dequeue(struct Queue* queue) { 
    if (is_empty(queue)) {
        printf("Error on dequeue: queue is empty\n");
        exit(EXIT_FAILURE);
    }

    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int front(struct Queue* queue) {
    return queue->data[queue->front];
}

int rear(struct Queue* queue) {
    return queue->data[queue->rear - 1];
}

int main() {

    struct Queue* queue = create_queue(5);

    enqueue(queue, 2);
    enqueue(queue, 9);
    enqueue(queue, 3);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));

    dequeue(queue);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));

    enqueue(queue, 10);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));
    
    return 0;
}