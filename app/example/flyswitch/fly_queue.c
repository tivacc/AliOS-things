#include "fly_queue.h"

int queue_init(queue_t * Q, unsigned char *buf,int size) {
    Q->head = 0;
    Q->tail = 0;
    Q->count = 0;
    Q->size = size;
    Q->array = buf;

    return 1;
}

int queue_empty(queue_t * Q) {
    if (Q->array == NULL) {
        return 1;
    }
    if (Q->count == 0)
        return 1;
    else 
        return 0;
}
int queue_enqueue(queue_t * Q, unsigned char item) {
    if (Q->array == NULL) {
        return 0;
    }
    if (Q->count < Q->size) {
        Q->array[Q->head] = item;
        Q->head = (Q->head + 1) % Q->size;
        Q->count++;
        return 1;
    } 
    else {
        return 0;
    }
}
int queue_dequeue(queue_t * Q, unsigned char *item) {
    if (Q->array == NULL) {
        return 0;
    }
    if (!queue_empty(Q)) {
        *item = Q->array[Q->tail];
        Q->tail = (Q->tail + 1) % Q->size;
        Q->count--;
        return 1;
    } else {
        return 0;
    }
}