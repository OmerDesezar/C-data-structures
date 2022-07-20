/*
    team: OL125-126    
    version: 2.0.2

*/
#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h> /* size_t */

struct slist;
struct slist_node;

typedef struct slist *slist_ptr_t;
typedef struct slist slist_t;
typedef struct slist_node *slist_node_ptr_t;
typedef slist_node_ptr_t slist_iter_t;

typedef int (*is_match_t)(const void *data, const void *param);
typedef int (*slist_action_t)(void *data, void *param);

/*
struct slist
{
	slist_node *head;
	slist_node *tail;
}

struct slist_node
{
	void *data;
	slist_node *next;
}

 * DESCRIPTION:
 * Function creates an empty list
 *
 * PARAMS:
 * none
 *         
 * RETURN:
 * Returns a pointer to the head of the list
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: O(1)
 */
slist_ptr_t SListCreate(void);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given list.
 * passing an invalid head pointer would result in undefined behaviour
 *
 * PARAMS:
 * list - pointer to the list to be destroyed
 *         
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void SListDestroy(slist_ptr_t list);

/* DESCRIPTION:
 * Function finds given nodes given a range, based on is_match function's 
 * return value.
 * passing an invalid iterator would result in undefined behaviour.
 * Trying to find an empty node will result in undefined behavior.
 *
 * PARAMS:
 * from 		- iterator to the part of the list to start from 
 * to           - iterator to the end of the iteration
 * func         - function to check if the values match
 * data         - element to find
 * func
 *         
 * RETURN:
 * iterator to the found data if not found it will return iterator "to" that inserted.
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, is_match_t func, void *data);

/* DESCRIPTION:
 * Function removes the selected element from the list.
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * iterator - selected element to remove.
        
 * RETURN:
 * void
 * COMPLEXITY: 
 * time: O(1)
 * space: O(1)
 */
void SListRemove(slist_iter_t iter);

/* DESCRIPTION:
 * Function returns the data of the given element after inserting it before the given iterator.
 * passing an invalid iterator would result in undefined behaviour.
 * passing an invalid data would result in undefined behaviour.
 *
 * PARAMS:
 * place_to_insert - iterator position in the list to enter before
 * data - the data to insert
 *      
 * RETURN:															
 * an iterator to the data that has been inserted if not returns the given iterator again (place_to_insert).
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
slist_iter_t SListInsertBefore(slist_iter_t place_to_insert, const void *data);

/* DESCRIPTION:
 * Function returns the number of elements on the list.
 * passing an invalid list would result in undefined behaviour.
 *
 * PARAMS:
 * list - head of the list to count from
 *      
 * RETURN:
 * number of elements
 * COMPLEXITY:
 * time: O(n) 
 * space: O(1)
 */
size_t SListCount(const slist_ptr_t list);

/* DESCRIPTION:
 * Function gets the data in the iterator's place
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * iter - iterator to the list to access from
 *         
 * RETURN:
 * Returns a pointer to the data that has been accessed,
 * NULL if the list is empty
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
const void *SListGetData(const slist_iter_t iter);

/* DESCRIPTION:
 * Function set the data of the given element.
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * iter - iterator to the list to set
 * data - new data to set
 *      
 * RETURN:
 * void.
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void SListSetData(slist_iter_t iter, void *data);

/* DESCRIPTION:
 * Function performs an action on each element in a given range.
 * passing an invalid iterator would result in undefined behaviour.
 * PARAMS:
 * from         - iterator to the part of the list to start from 
 * to           - iterator to the end of the iteration
 * action_func  - function pointer to perform an action on an element
 * param        - element for action function
 *      
 * RETURN:
 * 0 if succes 1 else.
 * time: O(n)
 * space: O(1)
 */
int SListForEach(slist_iter_t from, slist_iter_t to, slist_action_t action_func, void *param); 

/* DESCRIPTION:
 * Function returns an iterator to the next element in the list.
 * passing an invalid iterator would result in undefined behaviour.
 * PARAMS:
 * iter         - iterator of the part of the list to get the next from.
 *      
 * RETURN:
 * iterator to the next element.
 * time: O(1)
 * space: O(1)
 */
slist_iter_t SListIterNext(slist_iter_t iter);


/* DESCRIPTION:
 * Function returns an iterator to the beginning of the list.
 * passing an empty list would result in undefined behaviour.
 * PARAMS:
 * list         - pointer to start of the list 
 *      
 * RETURN:
 * iterator to the start of the list.
 * 
 * time: O(1)
 * space: O(1)
 */
slist_iter_t SListBegin(const slist_ptr_t list);

/* DESCRIPTION:
 * Function returns an iterator to the end of the list.
 * passing an empty list would result in undefined behaviour.
 * PARAMS:
 * list         - pointer to start of the list 
 *      
 * RETURN:
 * iterator to the end of the list.
 * 
 * time: O(1)
 * space: O(1)
 */
slist_iter_t SListEnd(const slist_ptr_t list);

/* DESCRIPTION:
 * Function compares between two iterators.
 * passing an invalid iterator would result in undefined behaviour.
 * 
 * PARAMS:
 * iter_one         - first iterator to compare 
 * iter_two         - second iterator to compare
 * 
 * RETURN:
 * 0 when iterators are identical, 1 otherwise.
 * 
 * time: O(1)
 * space: O(1)
 */
int SListIsIterEqual(slist_iter_t iter_one, slist_iter_t iter_two);

/* DESCRIPTION:
 * Function Append slist_dest and slist_src into slist_dest and empty slist_src.
 * passing an invalid qdest would result in undefined behaviour.
 * passing an invalid slist_src would result in undefined behaviour.
 * 
 *    PARAMS:
 * slist_dest -  pointer to the queue to append to.
 * slist_src - pointer to the queue to append from.
 *
 * RETURN:
 * void
 *    
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
void SListAppend(slist_ptr_t slist_dest, slist_ptr_t slist_src);

#endif /* __list_H__ */

