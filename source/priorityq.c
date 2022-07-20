/*=========================== LIBRARIES & MACROS ============================*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "priorityq.h"
#include "sortedlist.h"

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct priority_q
{
	sorted_list_t *list;
};

/* Reviewed by Adir */

priority_q_t *PriorityQCreate(priority_q_cmp_t func)
{
	priority_q_t *queue = NULL;
	
	assert(NULL != func);
	
	queue = (priority_q_t*) malloc(sizeof(priority_q_t));
	
	if(NULL != queue)
	{
		queue->list = SortedListCreate(func);
		if(NULL == (queue->list))
		{
			free(queue);
			queue = NULL;
		}
	}
	
	return (queue);
}

void PriorityQDestroy(priority_q_t *queue)
{
	assert(NULL != queue);
	
	SortedListDestroy(queue->list);
	queue->list = NULL;
	free(queue);
}

void PriorityQClear(priority_q_t *queue)
{
	assert(NULL != queue);
	
	while(!PriorityQIsEmpty(queue))
	{
		SortedListRemove(SortedListBegin(queue->list));
	}
}

int PriorityQEnqueue(priority_q_t *queue, void *data)
{
	assert(NULL != queue);
	
	return (!SortedListIsSameIter(SortedListEnd(queue->list), SortedListInsert(queue->list, data)));
}

void *PriorityQDequeue(priority_q_t *queue)
{
	assert(NULL != queue);
	
	return (SortedListPopBack(queue->list));
}

void *PriorityQErase(priority_q_t *queue, priority_q_is_match_t is_match, const void *param)
{
	sorted_list_iter_t found;
	void* data = NULL;
	
	assert(NULL != queue);
	assert(NULL != is_match);
	
	found = SortedListFindIf(SortedListBegin(queue->list),
			 SortedListEnd(queue->list), is_match, param);
	
	data = SortedListGetData(found);
	
	if(!SortedListIsSameIter(found, SortedListEnd(queue->list)))
	{
		SortedListRemove(found);
	}
	
	return (data);
}

void *PriorityQPeek(const priority_q_t *queue)
{
	assert(NULL != queue);
	
	return (SortedListGetData(SortedListIterPrev(SortedListEnd(queue->list))));
}

int PriorityQIsEmpty(const priority_q_t *queue)
{
	assert(NULL != queue);
	
	return (SortedListIsEmpty(queue->list));
}

size_t PriorityQSize(const priority_q_t *queue)
{
	assert(NULL != queue);
	
	return (SortedListSize(queue->list));
}


