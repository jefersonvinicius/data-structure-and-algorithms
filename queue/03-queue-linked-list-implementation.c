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
}


struct Queue* create_queue() {
    struct Queue *queue = malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int queue_is_empty(struct Queue* queue) {
    return queue->front == NULL;
}

void enqueue(struct Queue *queue, int value) {
    struct Node* newNode = create_node(value);
    if (queue_is_empty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        struct Node* tmp = queue->rear;
        queue->rear = newNode;
        queue->rear->next = tmp;
    }
}

int main() {

    struct Queue *queue = create_queue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    printf("%d\n", queue->front->data);
    printf("%d\n", queue->rear->data);

    return 0;
}