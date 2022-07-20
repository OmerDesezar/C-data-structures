/*============================LIBRARIES & MACROS =============================*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "../include/queue.h"
#include "../include/slist.h" /* most of slist funcs */

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

/* Approved by itamar */

typedef struct queue
{
	slist_ptr_t slist;
	size_t size;
}q_t;


queue_ptr_t QCreate(void)
{
	queue_ptr_t queue = (queue_ptr_t) malloc(sizeof(q_t));
	
	if(NULL == queue)
	{
		return (NULL);
	}
	
	queue->size = 0;
	queue->slist = SListCreate();
	
	if(NULL == queue->slist)
	{
		free(queue);
		return (NULL);
	}
	
	return (queue);
}

void QDestroy(queue_ptr_t queue)
{
	assert(NULL != queue);
	
	SListDestroy(queue->slist);
	free(queue);
}

q_status_t QEnQueue(queue_ptr_t queue, const void *element)
{
	assert(NULL != queue);
	
	++queue->size;
	
	return (NULL == SListInsertBefore(SListEnd(queue->slist), element));
}

void QDeQueue(queue_ptr_t queue)
{
	assert(NULL != queue);
	
	--queue->size;
	SListRemove(SListBegin(queue->slist));
}

void *QPeek(const queue_ptr_t queue)
{
	assert(NULL != queue);
	
	return((void*)SListGetData(SListBegin(queue->slist)));
}

void QAppend(queue_ptr_t qdest, queue_ptr_t qsrc)
{
	assert(NULL != qdest);
	assert(NULL != qsrc);
	
	qdest->size += qsrc->size;
	qsrc->size = 0;
	SListAppend(qdest->slist, qsrc->slist);
}

size_t QGetSize(const queue_ptr_t queue)
{
	assert(NULL != queue);
	
	return (queue->size);
}


int QIsEmpty(const queue_ptr_t queue)
{
	assert(NULL != queue);
	
	return (0 == queue->size);
}


