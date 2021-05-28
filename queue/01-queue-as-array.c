#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int currentIndex;
    int max;
    int *data;
};

struct Queue* create_queue(int max) {
    struct Queue* queue = malloc(sizeof(int) + sizeof(int) * max);
    queue->currentIndex = -1;
    queue->max = max;
    queue->data = malloc(sizeof(int) * max);
    return queue;
}

int is_empty(struct Queue* queue) {
    return queue->currentIndex == -1;
}

int is_full(struct Queue* queue) {
    return queue->currentIndex >= queue->max - 1;
}

void enqueue(struct Queue** queue, int value) {
    if (is_full(*queue)) {
        printf("Error on enqueue: queue is full\n");
        exit(EXIT_FAILURE);
    }

    (*queue)->data[++(*queue)->currentIndex] = value;
}

void dequeue(struct Queue* queue, int value) { // Wrong
    printf("QUEUE: %p\n", queue);
    if (is_empty(queue)) {
        printf("Error on dequeue: queue is empty\n");
        exit(EXIT_FAILURE);
    }

    queue->currentIndex--;
}

int front(struct Queue* queue) {
    return queue->data[0];
}

int rear(struct Queue* queue) {
    return queue->data[queue->currentIndex];
}

int main() {

    struct Queue* queue = create_queue(5);

    // printf("QUEUE OUT: %p\n", queue);

    // printf("is_empty: %d\n", is_empty(queue));
    // printf("is_full: %d\n", is_full(queue));

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));

    dequeue(queue, 1);

    printf("front: %d\n", front(queue));
    printf("rear: %d\n", rear(queue));


    return 0;
}