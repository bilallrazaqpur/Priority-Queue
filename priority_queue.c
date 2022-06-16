#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

int power(int x, int y) 
{
	int result = 1;
	for (int i = 0; i < y; i++)
		result = result * x;
	return result;
}

struct Heap
{
	int* value;
	unsigned* key;
};

struct Heap* heapCreate(unsigned maxSize)
{
	struct Heap* heap = malloc(sizeof(struct Heap*));
	heap->value = malloc(sizeof(int) * maxSize);
	heap->key = malloc(sizeof(unsigned) * maxSize);
	return heap;
}

struct PriorityQueue
{
	struct Heap* heap;
	unsigned maxSize;
	unsigned numElements;
};

struct PriorityQueue* pqCreate(unsigned maxSize)
{
    if (maxSize == 0)
		return NULL;
	struct PriorityQueue* pq = malloc(sizeof(struct PriorityQueue*));
	pq->heap = heapCreate(maxSize);
	pq->maxSize = maxSize;
	pq->numElements = 0;
    return pq;
}

int getParent(int index) 
{
	int parent = (index - 1 ) / 2;
	return parent;
}

int getLeft(int index)
{
	int left = index * 2 + 1;
	return left;
}

int getRight(int index)
{
	int right = index * 2 + 2;
	return right;
}

int heapMin(struct Heap** heap, int index) 
{ 
	if (index < 1)
		return 0;
	int parent = getParent(index);
	if ((*heap)->key[index] < (*heap)->key[parent]) {
		int tempVal = (*heap)->value[index];
		int tempKey = (*heap)->key[index];
		(*heap)->value[index] = (*heap)->value[parent];
		(*heap)->key[index] = (*heap)->key[parent];
		(*heap)->value[parent] = tempVal; 
		(*heap)->key[parent] = tempKey;
		heapMin(heap, parent);
	}
	return 1;
}

int pqFindKey(struct PriorityQueue* pq, unsigned key)
{
	for (int i = 0; i < pq->numElements; i++) {
		if (pq->heap->key[i] == key)
			return 1;
	}
	return 0;
}

int heapDestroy(struct Heap** heap)
{
	if (!heap)
		return 0;
	free((*heap)->value);
	free((*heap)->key);
	free(*heap);
	(*heap)->value = NULL;
	(*heap)->key = NULL;
	*heap = NULL;
	return 1;
}

int pqDestroy(struct PriorityQueue** pq)
{
    if (!pq)
		return 0;
	heapDestroy(&(*pq)->heap); 
	free(*pq);
	*pq = NULL;
    return 1;
}

int pqNumElements(const struct PriorityQueue* pq, unsigned* numElements)
{
    if (!pq || !numElements)
		return 0;
	*numElements = pq->numElements;
    return 1;
}

int pqMaxSize(const struct PriorityQueue* pq, unsigned* maxSize)
{
    if (!pq || !maxSize)
		return 0;
	*maxSize = pq->maxSize;
    return 1;
}

int pqPrint(const struct PriorityQueue* pq)
{
    if (!pq || pq->numElements == 0)
		return 0;
	int layer = 1;
	for (int i = 0; i < pq->numElements; i++) {
		printf("(%d,%d)", pq->heap->key[i], pq->heap->value[i]);
		if (i == (power(2, layer) - 2)) {
			printf("\n");
			layer++;
			continue;
		}
		if (i == pq->numElements - 1) {
			printf("\n");
			break;
		}
		printf(" ");
	}
    return 1;
}

int pqInsert(struct PriorityQueue* pq, unsigned key, int value)
{ 
    if ((pq->numElements == pq->maxSize) || (pqFindKey(pq, key) == 1))
		return 0;
	pq->heap->key[pq->numElements] = key;
	pq->heap->value[pq->numElements] = value;
	heapMin(&pq->heap, pq->numElements);
	pq->numElements++; 
    return 1;
}

int pqGetMinKey(const struct PriorityQueue* pq, unsigned* minKey)
{
    if (!pq || !minKey)
		return 0;
	*minKey = pq->heap->key[0];
    return 1;
}

int pqGetMinValue(const struct PriorityQueue* pq, int* minValue)
{
    if (!pq || !minValue)
		return 0;
	*minValue = pq->heap->value[0];
    return 1;
}

int pqDeleteMin(struct PriorityQueue* pq) 
{
    if (!pq || pq->numElements == 0)
		return 0;
	pq->numElements--;
	pq->heap->value[0] = pq->heap->value[pq->numElements];
	pq->heap->key[0] = pq->heap->key[pq->numElements];
	int left;
	int right;
	int tempVal;
	int min;
	unsigned tempKey;
	for (int i = 0; i < pq->numElements; i++) {
		left = getLeft(i);
		right = getRight(i);
		min = i;
		tempKey = pq->heap->key[i];
		tempVal = pq->heap->value[i];
		if (left < pq->numElements && pq->heap->key[left] < pq->heap->key[min]) {
			min = left;
		}
		if (right < pq->numElements && pq->heap->key[right] < pq->heap->key[min]) {
			min = right;
		}
		if (min == i)
			continue;
		pq->heap->key[i] = pq->heap->key[min];
		pq->heap->value[i] = pq->heap->value[min];
		pq->heap->key[min] = tempKey;
		pq->heap->value[min] = tempVal;
	}
    return 1;
}

