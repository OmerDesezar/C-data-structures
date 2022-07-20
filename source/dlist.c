/*============================LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "dlist.h"

#define TRUE 1
#define FALSE 0

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
};

struct dlist
{
	dlist_node_t head; 
	dlist_node_t tail;
};

dlist_t *DoublyListCreate(void)
{
	dlist_t *list = (dlist_t*) malloc(sizeof(dlist_t));
	
	if(NULL != list)
	{
		list->head.data = NULL;
		list->head.next = &list->tail;
		list->head.prev = NULL;
			
		list->tail.data = NULL;
		list->tail.next = NULL;
		list->tail.prev = &list->head;
	}
	
	return (list);
}

void DoublyListDestroy(dlist_t *list)
{
	dlist_iter_t current_node = NULL;
    assert (NULL != list);
    
    current_node = DoublyListBegin(list);
	
	while (NULL != current_node->next)
	{
		current_node = DoublyListRemove(current_node);
	}

    free(list); 
}

dlist_iter_t DoublyListInsertBefore(dlist_t *list, dlist_iter_t where, const void *data)
{
	dlist_node_t *new_node = NULL;
	
	assert(NULL != where);
	assert(NULL != list);
	
	new_node = (dlist_node_t*) malloc(sizeof(dlist_node_t));
	
	if(NULL == new_node)
	{
		new_node = DoublyListEnd(list);
	}
	else
	{
		new_node->data = (void*)data;
		new_node->next = where;
		new_node->prev = where->prev;
		where->prev->next = new_node;
		where->prev = new_node;
	}
	
	return (new_node);
}

dlist_iter_t DoublyListRemove(dlist_iter_t where)
{
	dlist_iter_t next = NULL;
	
	assert(NULL != where);
	assert(NULL != where->next);
	assert(NULL != where->prev);
	
	next = DoublyListIterNext(where);
	where->next->prev = where->prev;
	where->prev->next = where->next;
	where->data = 0;
	
	free(where);
	
	return (next);
}

dlist_iter_t DoublyListPushBack(dlist_t *list, void *data)
{
	assert(NULL != list);
	
	return (DoublyListInsertBefore(list, DoublyListEnd(list), data));
}

dlist_iter_t DoublyListPushFront(dlist_t *list, void *data)
{
	assert(NULL != list);
	
	return (DoublyListInsertBefore(list, DoublyListBegin(list), data));
}

void *DoublyListPopBack(dlist_t *list)
{
	void *data= NULL;
	dlist_iter_t to_pop = NULL;
	
	assert(NULL != list);
	
	to_pop = DoublyListIterPrev(DoublyListEnd(list));
	data = DoublyListGetData(to_pop);
	DoublyListRemove(to_pop);
	
	return (data);
}

void *DoublyListPopFront(dlist_t *list)
{
	void *data= NULL;
	dlist_iter_t to_pop = NULL;
	
	assert(NULL != list);
	
	to_pop = DoublyListBegin(list);
	data = DoublyListGetData(to_pop);
	DoublyListRemove(to_pop);
	
	return (data);
}

dlist_iter_t DoublyListFind(const dlist_iter_t from, const dlist_iter_t to, is_match_t IsMatch, const void *param)
{
	int is_found = FALSE;
	dlist_iter_t runner = from;
	
	assert(NULL != from);
	assert(NULL != to);
	
	while(!(DoublyListIsSameIter(runner, to)))
	{
		is_found = IsMatch(runner->data, param);
		if(is_found == TRUE)
		{
			break;
		}
		runner = DoublyListIterNext(runner);
	}
	
	return (runner);
}

int DoublyListMultiFind(const dlist_iter_t from, const dlist_iter_t to, 
		         is_match_t IsMatch, const void *param, dlist_t *dest_list)
{
	int is_found = FALSE;
	dlist_iter_t runner = from;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != param);
	
	while(!(DoublyListIsSameIter(runner, to)))
	{
		if(IsMatch(runner->data, param) == TRUE)
		{
			is_found = TRUE;
			DoublyListInsertBefore(dest_list, DoublyListEnd(dest_list), runner->data);
		}
		runner = DoublyListIterNext(runner);
	}
	return (is_found);
}

size_t DoublyListSize(const dlist_t *list)
{
	size_t counter = 0;
	dlist_iter_t runner = NULL;
	
	assert(NULL != list);
	
	runner = DoublyListBegin(list);
	
	while(runner->next != NULL)
	{
		++counter;
		runner = DoublyListIterNext(runner);
	}
    return (counter);
}

int DoublyListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);

	return (list->head.next == &list->tail);
}

void *DoublyListGetData(const dlist_iter_t where)
{
	assert(NULL != where);
	
	return (where->data);
}

void DoublyListSetData(dlist_iter_t where, void *data)
{
	assert(NULL != where);
	
	where->data = data;
}

int DoublyListForEach(dlist_iter_t from, dlist_iter_t to, dlist_action_t action_func, void *param)
{
	int status = 0;
	dlist_iter_t runner = from;
	
	assert(NULL != from);
	assert(NULL != to);
	
	while(!(DoublyListIsSameIter(runner, to)) && (0 == status))
	{
		status = action_func(runner->data, param);
		runner = DoublyListIterNext(runner);
	}
	
	return (status);
}

dlist_iter_t DoublyListIterNext(const dlist_iter_t where)
{
	assert(NULL != where);
	assert(NULL != where->next);
	
	return (where->next);
}

dlist_iter_t DoublyListIterPrev(const dlist_iter_t where)
{
	assert(NULL != where);
	assert(NULL != where->prev);
	
	return (where->prev);
}

dlist_iter_t DoublyListBegin(const dlist_t *list)
{
	assert(NULL != list);
	
	return (list->head.next);
}

dlist_iter_t DoublyListEnd(const dlist_t *list)
{
	assert(NULL != list);
	
	return ((dlist_iter_t)&list->tail);
}

int DoublyListIsSameIter(const dlist_iter_t iter_one, const dlist_iter_t iter_two)
{
	assert(NULL != iter_one);
	assert(NULL != iter_two);
	
	return (iter_one == iter_two);
}

dlist_iter_t DoublyListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	dlist_node_t *to_prev = to->prev;
	dlist_node_t *where_prev = where->prev;
	
	assert(NULL != where);
	assert(NULL != to);
	assert(NULL != from);
	
	to->prev = from->prev;
	from->prev->next = to;
	
	from->prev = where_prev;
	where_prev->next = from;
	
	to_prev->next = where;
	where->prev = to_prev;
	
	return (from);

}



