#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct PriorityQueue;

struct PriorityQueue* pqCreate(unsigned maxSize);

int pqDestroy(struct PriorityQueue** pq);

int pqNumElements(const struct PriorityQueue* pq, unsigned* numElements);

int pqMaxSize(const struct PriorityQueue* pq, unsigned* maxSize);

int pqPrint(const struct PriorityQueue* pq);

int pqInsert(struct PriorityQueue* pq, unsigned key, int value);

int pqGetMinKey(const struct PriorityQueue* pq, unsigned* minKey);

int pqGetMinValue(const struct PriorityQueue* pq, int* minValue);

int pqDeleteMin(struct PriorityQueue* pq);

#endif  // PRIORITY_QUEUE_H
