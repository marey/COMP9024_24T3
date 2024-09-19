#ifndef QUEUE_H
#define QUEUE_H

typedef long QUEUE_ITEM_T;

struct Queue;

struct Queue *CreateQueue(void);

void ReleaseQueue(struct Queue *pQueue);

void QueueEnqueue(struct Queue *pQueue, QUEUE_ITEM_T item);

QUEUE_ITEM_T QueueDequeue(struct Queue *pQueue);

int QueueIsEmpty(struct Queue *pQueue);

QUEUE_ITEM_T QueuePeek(struct Queue *pQueue);

// for debugging
void PrintQueue(struct Queue *pQueue);

long QueueLength(struct Queue *pQueue);


void QueueGenOneImage(struct Queue *pQueue, char *graphName, char *fileName, long seqNo);

#endif


