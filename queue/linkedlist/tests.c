#include "queue.h"
#include "assert.h"

int main() {

    { // should create queue correctly
        struct LklQueue *queue = create_lkl_queue();
        assert(queue->front == NULL);
    }

    { // should enqueue correctly
        struct LklQueue *queue = create_lkl_queue();
        assert(queue->front == NULL);
        lklq_enqueue(queue, 1);
        assert(queue->front->data == 1);
        lklq_enqueue(queue, 2);
        assert(queue->front->data == 1);
        lklq_enqueue(queue, 3);
        assert(queue->front->data == 1);
        assert(queue->front->next->data == 2);
        assert(queue->front->next->next->data == 3);
        lklq_enqueue(queue, 4);
        assert(queue->front->data == 1);
        assert(queue->front->next->data == 2);
        assert(queue->front->next->next->data == 3);
        assert(queue->front->next->next->next->data == 4);
        assert(queue->front->next->next->next->next == NULL);
    }

    { // should dequeue correctly
        struct LklQueue *queue = create_lkl_queue();
        assert(queue->front == NULL);
        lklq_enqueue(queue, 1);
        lklq_dequeue(queue);
        assert(queue->front == NULL);
        lklq_enqueue(queue, 1);
        lklq_enqueue(queue, 2);
        lklq_dequeue(queue);
        assert(queue->front->data == 2);
        assert(queue->front->next == NULL);
        lklq_dequeue(queue);
        assert(lklq_is_empty(queue) == 1);
        lklq_enqueue(queue, 1);
        lklq_enqueue(queue, 2);
        lklq_enqueue(queue, 3);
        lklq_dequeue(queue);
        assert(queue->front->data == 2);
        assert(queue->front->next->data == 3);
        assert(queue->front->next->next == NULL);
    }

    
    return 0;
}