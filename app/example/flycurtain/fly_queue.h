#include <stdio.h>
#include <stdlib.h>

typedef struct QUEUE
{
    int head;
    int tail;
    int count;
    int size;
    unsigned char *array;
} queue_t;

int queue_init(queue_t * Q, unsigned char *buf,int size);
int queue_empty(queue_t * Q);
int queue_enqueue(queue_t * Q, unsigned char item);
int queue_dequeue(queue_t * Q, unsigned char *item);