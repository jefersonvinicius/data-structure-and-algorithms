#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Item {
    int data;
    int priority;
};

struct PriorityQueue {
    struct Item **items;
    int size, current_index;
};

struct Item* create_item(int data, int priority) {
    struct Item* item = malloc(sizeof(struct Item));
    item->data = data;
    item->priority = priority;
    return item;
}

struct PriorityQueue* create_queue(int size) {
    struct PriorityQueue* queue = malloc(sizeof(struct PriorityQueue));
    queue->items = malloc(sizeof(struct Item) * size);
    queue->size = size;
    queue->current_index = 0;
    return queue;
}

void enqueue(struct PriorityQueue* queue, int data, int priority) {
    struct Item* item = create_item(data, priority);
    queue->items[queue->current_index] = malloc(sizeof(struct Item));
    queue->items[queue->current_index++] = item;
}

void dequeue(struct PriorityQueue* queue) {
    int biggerPriorityValue = INT_MIN;
    int biggerPriorityIndex = 0;
    for (int i = 0; i < queue->current_index; i++) {
        if (queue->items[i]->priority > biggerPriorityValue) {
            biggerPriorityIndex = i;
            biggerPriorityValue = queue->items[i]->priority;
        }
    }
    if (biggerPriorityIndex < queue->current_index - 1) { 
        // this operation can be costly compared to linked list implementation
        for (int i = biggerPriorityIndex; i < queue->current_index; i++) {
            queue->items[i] = queue->items[i + 1];
        }
    }
    free(queue->items[queue->current_index - 1]);
    queue->current_index--;
}



struct Item* front(struct PriorityQueue* queue) {
    return queue->items[0];
}

struct Item* rear(struct PriorityQueue* queue) {
    return queue->items[queue->current_index - 1];
}

int main() {
    struct PriorityQueue *queue = create_queue(10);
    enqueue(queue, 1, 1);
    enqueue(queue, 2, 3);
    enqueue(queue, 3, 4);

    printf("FRONT: %d - %d\n", front(queue)->data, front(queue)->priority);
    printf("REAR: %d - %d\n", rear(queue)->data, rear(queue)->priority);

    dequeue(queue);

    printf("FRONT: %d - %d\n", front(queue)->data, front(queue)->priority);
    printf("REAR: %d - %d\n", rear(queue)->data, rear(queue)->priority);
}