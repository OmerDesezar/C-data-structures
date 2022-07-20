/*
    team: OL125-126    
    version: 1.0

*/
#ifndef _hasht_H_
#define _hasht_H_

#include <stddef.h> /* size_t */
#include "dlist.h"

typedef size_t (*hash_func_t)(const void *key);
typedef int (*action_func_t)(void *data, void *param);
typedef int (*hash_is_match_t)(const void *key1, const void *key2);
typedef struct hasht hasht_t;

/* DESCRIPTION:
 * Function creates an empty hash table
 *
 * PARAMS:
 * expected_capacity - maximum number of elemenets in the table
 * hash_func - hash function of the table
 * cmp_func - comparison function to find elements 
 *         
 * RETURN:
 * Returns a pointer to the created hash table
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
hasht_t *HashtCreate(size_t expected_capacity, hash_is_match_t cmp_func, hash_func_t hash_func);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given table.
 * passing an invalid table pointer would result in undefined behaviour
 * This function should be used when finshing using the table.
 *
 * PARAMS:
 * table - pointer to the table to be destroyed
 *         
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void HashtDestroy(hasht_t *table);

/* DESCRIPTION:
 * Function checks whether the table is empty
 *
 * PARAMS:
 * table - pointer to the table to check if empty
 *         
 * RETURN:
 * 1 if the table is empty or 0 otherwise
 *
 * COMPLEXITY:
 * time: O(k) 
 * space: O(1)
 */
int HashtIsEmpty(const hasht_t *table);

/* DESCRIPTION:
 * Function inserts the key to the table and returns the corresponding key.
 * passing an invalid table would result in undefined behaviour.
 *
 * PARAMS:
 * table- table to insert the data to
 * data - the data to insert
 *      
 * RETURN:															
 * 0 if success, 1 otherwise.
 *
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
int HashtInsert(hasht_t *table, void *data);

/* DESCRIPTION:
 * Function removes the selected key from the table.
 * passing an invalid table would result in undefined behaviour.
 *
 * PARAMS:
 * table- hasht to insert the data to
 * key - key to find data to be deleted
 *      
 * RETURN:
 * void 
 *
 * COMPLEXITY: 
 * O(1)
 * space: O(1)
 */
void HashtRemove(hasht_t *table, void *key);

/* DESCRIPTION:
 * Function finds data in the table based on the given key.
 * passing invalid table would result in undefined behaviour.
 *
 * PARAMS:
 * table	 - pointer to the table to search in 
 * key       	 - key to search 
 *         
 * RETURN:
 * pointer to the found data. if not found, it will return NULL.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void *HashtFind(const hasht_t *table, const void *key);

/* DESCRIPTION:
 * Function returns the number of elements in the table.
 * passing an invalid table would result in undefined behaviour.
 *
 * PARAMS:
 * table - pointer to a table 
 *      
 * RETURN:
 * number of elements
 *
 * COMPLEXITY:
 * time: O(n) 
 * space: O(1)
 */
size_t HashtSize(const hasht_t *table);

/* DESCRIPTION:
 * Function performs an action on each element in the given table.
 * passing an invalid table would result in undefined behaviour.
 *
 * PARAMS:
 * table - pointer to a table
 * action_func  - function pointer to an action to perform on a node
 * param        - element for action function
 *      
 * RETURN:
 * 0 if succes 1 else.
 * time: O(n)
 * space: O(1)
 */
int HashtForEach(hasht_t *table, action_func_t action_func, void *param); 

double HashtLoad(const hasht_t *table);

double HashtStandardDeviation(const hasht_t *table);

void SpellChecker();

#endif /* __hasht_H__ */

