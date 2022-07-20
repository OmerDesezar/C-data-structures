/*============================LIBRARIES & MACROS =============================*/

#include <stddef.h> /* Size_t */
#include <stdlib.h> /* Malloc, Free */
#include <assert.h> /* Assert */

#include "../include/slist.h"

/*=============================== DECLARATIONS ==============================*/

static int CounterFunc(void *ptr, void *param);

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

typedef struct slist
{
	slist_node_ptr_t head;
	slist_node_ptr_t tail;
}list_t;

typedef struct slist_node
{
	void *data;
	slist_node_ptr_t next;
}node_t;

/* Approved by Eliraz */

slist_ptr_t SListCreate(void)
{
	slist_node_ptr_t dummy = NULL;
	slist_ptr_t list = (slist_ptr_t) malloc(sizeof(list_t));
	
	if(NULL == list)
	{
		return (NULL);
	}
	
	dummy = (slist_node_ptr_t) malloc(sizeof(node_t));
	
	if(NULL == dummy)
	{
		return (NULL);
	}
	
	list->head = dummy;
	list->tail = dummy;

	dummy->data = list;
	dummy->next = NULL;

	
	return (list);
}

void SListDestroy(slist_ptr_t list)
{
    slist_node_ptr_t current_node = NULL;
    slist_node_ptr_t next_node = NULL;

    assert (NULL != list);
    
    current_node = list->head;
	
	while (NULL != current_node)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}

    free(list); 
}

slist_iter_t SListInsertBefore(slist_iter_t place_to_insert, const void *data)
{
	slist_node_ptr_t new_node = NULL;
	
	assert(NULL != place_to_insert);
	
	new_node = (slist_node_ptr_t) malloc(sizeof(node_t));
	
	if(NULL == new_node)
	{
		return (NULL);
	}
	
	new_node->data = place_to_insert->data;
	new_node->next = place_to_insert->next;
	
	if (NULL == new_node->next)
	{
		((slist_ptr_t)new_node->data)->tail = new_node;
	}
	
	place_to_insert->next = new_node;
	place_to_insert->data = (void*)data;
	
	return (place_to_insert);
}

void SListRemove(slist_iter_t iter)
{	
	slist_iter_t temp = NULL;
	
	assert(NULL != iter);	

	temp = SListIterNext(iter);
	iter->data = temp->data;
	iter->next = temp->next;
	if (NULL == iter->next)
    {
        ((slist_t*)(iter->data))->tail = iter;
    }
	free(temp);
}

void SListAppend(slist_ptr_t dest, slist_ptr_t src)
{
	slist_iter_t dest_dummy = SListEnd(dest);
    slist_iter_t src_head = SListBegin(src);
    slist_iter_t src_dummy = SListEnd(src);
    slist_node_ptr_t new_dummy = malloc(sizeof(node_t));
    
    if(NULL == new_dummy)
    {
    	return;
	}
    
    new_dummy->data = src;
    new_dummy->next = NULL;

    dest_dummy->next = src_head;
    dest->tail = src_dummy;
    src_dummy->data = dest;
    SListRemove(dest_dummy);
    src->head = new_dummy;
    src->tail = new_dummy;
}

const void *SListGetData(const slist_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->data);
}

void SListSetData(slist_iter_t iter, void *data)
{
	assert(NULL != iter);
	assert(NULL != data);
	
	iter->data = data;
}


size_t SListCount(const slist_ptr_t list)
{
	size_t counter = 0;
	slist_iter_t iter_start = NULL;
	slist_iter_t iter_end = NULL;

	assert (NULL != list);

	iter_start = SListBegin(list);
	iter_end = SListEnd(list);

	SListForEach(iter_start, iter_end, CounterFunc, (void*)&counter);

	return (counter);

}

int SListIsIterEqual(slist_iter_t iter_one, slist_iter_t iter_two)
{
	assert(NULL != iter_one);
	assert(NULL != iter_two);
	
	return (iter_one == iter_two);
}

slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, is_match_t match_func, void *data)
{
	int found = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != data);
	
	while(!(SListIsIterEqual(from, to)))
	{
		found = match_func(from->data, data);
		if(found == 1)
		{
			break;
		}
		from = SListIterNext(from);
	}
	return (from);
}


int SListForEach(slist_iter_t from, slist_iter_t to, slist_action_t action_func, void *param)
{
	int status = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	
	while(!(SListIsIterEqual(from, to)) && (0 == status))
	{
		status = action_func(from->data, param);
		from = SListIterNext(from);
	}
	
	return (status);
}

slist_iter_t SListIterNext(slist_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->next);
}

slist_iter_t SListBegin(const slist_ptr_t list)
{
	assert(NULL != list);
	
	return (list->head);
}

slist_iter_t SListEnd(const slist_ptr_t list)
{
	
	assert(NULL != list);
	
	return (list->tail);
}

static int CounterFunc(void *ptr, void *param)
{
	(void)ptr;
	
	++*(size_t*)param; 
	
	return (0);
}

