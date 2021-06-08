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

void print_queue(struct Queue* queue) {
    struct Node* currentNode = queue->rear;
    while (1) {
        if (currentNode != NULL) printf("NODE: (%p::%d) ", currentNode, currentNode->data);
        if (currentNode->next != NULL) printf("-> (%p::%d)", currentNode->next, currentNode->next->data);
        printf("\n");

        if (currentNode->next == NULL) break;
        currentNode = currentNode->next;
    }
}

int main() {

    struct Queue *queue = create_queue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);

    print_queue(queue);
    printf("front: %d\n", queue->front->data);
    printf("rear: %d\n", queue->rear->data);

    dequeue(queue);

    printf("%d\n", queue->front->data); 
    printf("%d\n", queue->rear->data);
    
    return 0;
}