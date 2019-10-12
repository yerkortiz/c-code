#include <stdio.h>

#define QUEUE_SIZE (1 << 4)
#define EXIT_PROGRAM return 0;

typedef struct
{
    int queue[QUEUE_SIZE];
    int front, tail, size;
} queue;
int empty(queue *q)
{
    return q->size == 0;
}
void enqueue(queue *q, int value)
{
    if(q->size < QUEUE_SIZE) {
        q->queue[((q->tail)++)] = value;
        (q->tail) = (q->tail + QUEUE_SIZE) % QUEUE_SIZE;
    }
}
void dequeue(queue *q)
{
    if(q->size > 1) {
        --(q -> front);
        (q -> front) = (q->tail + QUEUE_SIZE) % QUEUE_SIZE;
    }
    return 0;
}
int front(queue *q)
{
    return q->queue[q->front];
}
int main(void)
{
    EXIT_PROGRAM;
}