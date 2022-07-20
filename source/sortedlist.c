/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "sortedlist.h"

#define TRUE 0
#define FALSE 1

/*============================== DECLARATIONS ===============================*/

static sorted_list_iter_t DoublyToSorted(
dlist_iter_t doubly_iter, const sorted_list_t *list);
static void AssertLists(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct sortedlist
{
	dlist_t *dlist;
	sorted_list_cmp_t func;
};


sorted_list_t *SortedListCreate(sorted_list_cmp_t func)
{
	sorted_list_t *list = NULL;
	
	assert(NULL != func);
	
	list = (sorted_list_t*) malloc(sizeof(sorted_list_t));
	
	if(NULL != list)
	{
		list->func = func;
		list->dlist = DoublyListCreate();
		
		if(NULL == list->dlist)
		{
			free(list);
			list = NULL;
		}
	}
	
	return (list);
}

void SortedListDestroy(sorted_list_t *list)
{
	assert(NULL != list);
	
	DoublyListDestroy(list->dlist);
	free(list);
}

sorted_list_iter_t SortedListInsert(sorted_list_t *list, void *data)
{
	sorted_list_iter_t runner;
	
	assert(NULL != list);
	
	runner = SortedListBegin(list);
	
	if(!SortedListIsEmpty(list))
	{
		while(!SortedListIsSameIter(runner, SortedListEnd(list)) &&
		(0 > list->func(SortedListGetData(runner), data)))
		{
			runner = SortedListIterNext(runner);
		}
	}
	
	runner.internal_iter = DoublyListInsertBefore(
	list->dlist, runner.internal_iter, data);
	
	return (runner);
}

sorted_list_iter_t SortedListRemove(sorted_list_iter_t where)
{
	assert(NULL != where.internal_iter);
	
	where.internal_iter = DoublyListRemove(where.internal_iter);
	
	return (where);
}

void *SortedListPopBack(sorted_list_t *list)
{
	assert(NULL != list);
	
	return (DoublyListPopBack(list->dlist));
}

void *SortedListPopFront(sorted_list_t *list)
{
	assert(NULL != list);
	
	return (DoublyListPopFront(list->dlist));
}

void *SortedListGetData(const sorted_list_iter_t where)
{
	assert(NULL != where.internal_iter);
	
	return (DoublyListGetData(where.internal_iter));
}


sorted_list_iter_t SortedListFind(
const sorted_list_iter_t from,const sorted_list_iter_t to,
const sorted_list_t *list,const void *param)
{
	int is_found = FALSE;
	sorted_list_iter_t runner = from;
	
	assert(NULL != from.internal_iter);
	assert(NULL != to.internal_iter);
	assert(NULL != list);
	AssertLists(from, to);
	
	while(!(SortedListIsSameIter(runner, to)))
	{
		is_found = list->func(SortedListGetData(runner), param);
		if(is_found == TRUE)
		{
			break;
		}
		runner = SortedListIterNext(runner);
	}
	
	return (runner);
}

sorted_list_iter_t SortedListFindIf(
const sorted_list_iter_t from, const sorted_list_iter_t to,
sorted_list_is_match_t is_match, const void *param)
{
	sorted_list_iter_t sorted;
	
	assert(NULL != from.internal_iter);
	assert(NULL != to.internal_iter);
	assert(NULL != is_match);
	AssertLists(from,to);
	
	sorted.internal_iter = DoublyListFind(from.internal_iter, 
	to.internal_iter, is_match, param);
	
	#ifndef NDEBUG
	sorted.list = from.list;
	#endif

	return(sorted);
}

int SortedListForEach(
sorted_list_iter_t from, sorted_list_iter_t to, 
sorted_list_action_t action_func, void *param)
{
	assert(NULL != from.internal_iter);
	assert(NULL != to.internal_iter);
	assert(NULL != action_func);
	AssertLists(from, to);
	
	return(DoublyListForEach(
	from.internal_iter, to.internal_iter, action_func, param));
}

size_t SortedListSize(const sorted_list_t *list)
{
	assert(NULL != list);
	
	return (DoublyListSize(list->dlist));
}

int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);
	
	return (DoublyListIsEmpty(list->dlist));
}

sorted_list_iter_t SortedListIterNext(sorted_list_iter_t curr)
{
	assert(NULL != curr.internal_iter);
	
	curr.internal_iter = DoublyListIterNext(curr.internal_iter);
	
	return (curr);
}

sorted_list_iter_t SortedListIterPrev(sorted_list_iter_t curr)
{
	assert(NULL != curr.internal_iter);
	
	curr.internal_iter = DoublyListIterPrev(curr.internal_iter);
	
	return (curr);
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t iter;

	assert(NULL != list);
	
	iter = DoublyToSorted(DoublyListBegin(list->dlist), list);
	
	return (iter);
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t iter;

	assert(NULL != list);
	
	iter = DoublyToSorted(DoublyListEnd(list->dlist), list);
	
	return (iter);
}

int SortedListIsSameIter(
sorted_list_iter_t iter_one, sorted_list_iter_t iter_two)
{
	assert(NULL != iter_one.internal_iter);
	assert(NULL != iter_two.internal_iter);
	
	return(DoublyListIsSameIter(iter_one.internal_iter, iter_two.internal_iter));
}

void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iter_t src_from_runner;
	sorted_list_iter_t src_to_runner;
	sorted_list_iter_t dest_runner;
	
	assert(NULL != dest_list);
	assert(NULL != src_list);
	
	dest_runner = SortedListBegin(dest_list);
	src_from_runner = SortedListBegin(src_list);
	src_to_runner = src_from_runner;
	
	while(1)
	{
		if(SortedListIsSameIter(dest_runner, SortedListEnd(dest_list)) ||
		SortedListIsSameIter(src_to_runner, SortedListEnd(src_list)))
		{
			DoublyListSplice(
			src_from_runner.internal_iter, 
			SortedListEnd(src_list).internal_iter, 
			dest_runner.internal_iter);
			break;
		}
		
		if(0 > dest_list->func(
		SortedListGetData(dest_runner), SortedListGetData(src_from_runner)))
		{
			dest_runner = SortedListIterNext(dest_runner);
			continue;
		}
		
		if(0 <= dest_list->func(
		SortedListGetData(dest_runner), SortedListGetData(src_to_runner)))
		{
			src_to_runner = SortedListIterNext(src_to_runner);
			continue;
		}
		
		DoublyListSplice(
		src_from_runner.internal_iter,
		src_to_runner.internal_iter,
		dest_runner.internal_iter);
		
		src_from_runner = SortedListBegin(src_list);
		src_to_runner = src_from_runner;
	}
}


static sorted_list_iter_t DoublyToSorted(
dlist_iter_t doubly_iter, const sorted_list_t *list)
{
	sorted_list_iter_t iter;
	iter.internal_iter = doubly_iter;
	#ifndef NDEBUG
	iter.list = (sorted_list_t*) list;
	#endif
	(void)list;
	
	return (iter);
}

static void AssertLists(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	#ifndef NDEBUG
	assert(iter1.list == iter2.list);
	#endif
	(void)iter1;
	(void)iter2;
}



