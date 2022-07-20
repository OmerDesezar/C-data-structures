/*=========================== LIBRARIES & MACROS ============================*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "pq_heap.h"
#include "heap.h"

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct pq_heap
{
	bin_heap_t *heap;
};

pq_heap_t *PQHeapCreate(pq_heap_cmp_t func)
{
	pq_heap_t *queue = NULL;
	assert(NULL != func);
	queue = (pq_heap_t *)malloc(sizeof(pq_heap_t));

	if (NULL != queue)
	{
		queue->heap = BinHeapCreate(func);
		if (NULL == (queue->heap))
		{
			free(queue);
			queue = NULL;
		}
	}

	return (queue);
}

void PQHeapDestroy(pq_heap_t *queue)
{
	assert(NULL != queue);
	BinHeapDestroy(queue->heap);
	queue->heap = NULL;
	free(queue);
}

void PQHeapClear(pq_heap_t *queue)
{
	assert(NULL != queue);
	while (!PQHeapIsEmpty(queue))
	{
		BinHeapPop(queue->heap);
	}
}

int PQHeapEnqueue(pq_heap_t *queue, void *data)
{
	assert(NULL != queue);
	return (BinHeapPush(queue->heap, data));
}

void *PQHeapDequeue(pq_heap_t *queue)
{
	void *rtn = NULL;
	assert(NULL != queue);
	rtn = BinHeapPeek(queue->heap);
	BinHeapPop(queue->heap);
	return (rtn);
}

void *PQHeapErase(pq_heap_t *queue, pq_heap_is_match_t is_match, const void *param)
{
	assert(NULL != queue);
	assert(NULL != is_match);
	return (BinHeapRemove(queue->heap, is_match, (void *)param));
}

void *PQHeapPeek(const pq_heap_t *queue)
{
	assert(NULL != queue);
	return (BinHeapPeek(queue->heap));
}

int PQHeapIsEmpty(const pq_heap_t *queue)
{
	assert(NULL != queue);
	return (BinHeapIsEmpty(queue->heap));
}

size_t PQHeapSize(const pq_heap_t *queue)
{
	assert(NULL != queue);
	return (BinHeapSize(queue->heap));
}
