/*
    team: OL125-126    
    version: 1.0

*/
#ifndef _BST_H_
#define _BST_H_

#include <stddef.h> /* size_t */

typedef int (*action_func_t)(void *data, void *param);
typedef int (*cmp_func_t)(const void *data1, const void *data2);

typedef struct bst bst_t;
typedef struct bst_node bst_node_t;
typedef bst_node_t *bst_iter_t;

/* DESCRIPTION:
 * Function creates an empty bst
 *
 * PARAMS:
 * cmp_fun - pointer to the compare function
 *         
 * RETURN:
 * Returns a pointer to the created bst
 *
 * COMPLEXITY:
 * time: best - O(1)
 * space: O(1)
 */
bst_t *BSTCreate(cmp_func_t cmp_func);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given bst.
 * passing an invalid bst pointer would result in undefined behaviour
 * This function should be used when finshing using the bst.
 *
 * PARAMS:
 * tree - pointer to the bst to be destroyed
 *         
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void BSTDestroy(bst_t *tree);

/* DESCRIPTION:
 * Function checks whether the bst is empty
 *
 * PARAMS:
 * bst - pointer to the bst to check if empty
 *         
 * RETURN:
 * 1 if the bst is empty or 0 otherwise
 *
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
int BSTIsEmpty(const bst_t *tree);

/* DESCRIPTION:
 * Function returns the data of the given element after inserting it to the given bst.
 * passing an invalid tree would result in undefined behaviour.
 *
 * PARAMS:
 * tree - bst to insert the data to
 * data - the data to insert
 *      
 * RETURN:															
 * pointer to the node that has been inserted, NULL if fails
 *
 * COMPLEXITY:
 * average time: O(log n) , worst: O(n)
 * space: O(1)
 */
bst_iter_t BSTInsert(bst_t *tree, const void *data);

/* DESCRIPTION:
 * Function removes the selected element from the bst.
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * where - selected node to remove.
 *      
 * RETURN:
 * void 
 *
 * COMPLEXITY: 
 * time: O(log n), worst: O(n)
 * space: O(1)
 */
void BSTRemove(bst_iter_t where);

/* DESCRIPTION:
 * Function finds elements base on the return value of is_match function ,in a given range.
 * passing invalid iterators would result in undefined behaviour.
 *
 * PARAMS:
 * tree	        - pointer to the tree to search in 
 * param       	 - paramter to be passed to is_match func
 *         
 * RETURN:
 * iterator to the found data. if not found, it will return the iterator "to".
 *
 * COMPLEXITY:
 * time: O(log n) ,worst: O(n)
 * space: O(1)
 */
bst_iter_t BSTFind(bst_t *tree, const void *data);

/* DESCRIPTION:
 * Function returns the number of elements in the bst.
 * passing an invalid bst would result in undefined behaviour.
 *
 * PARAMS:
 * bst - pointer to a bst  
 *      
 * RETURN:
 * number of elements
 *
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
size_t BSTSize(const bst_t *tree);

/* DESCRIPTION:
 * Function gets the data in the iterator's place
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * where - iterator to the bst to get data from
 *         
 * RETURN:
 * Returns a pointer to the data that has been accessed.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void *BSTGetData(bst_iter_t where);

/* DESCRIPTION:
 * Function performs an action on each element in the given tree.
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * from 	- iter that indicate the starting point, included
 * to 		- iter that indicate the end point, excluded
 * action_func  - function pointer to an action to perform on a node
 * param        - element for action function
 *      
 * RETURN:
 * 0 if succes 1 else.
 * time: O(n)
 * space: O(1)
 */
int BSTForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, void *param); 

/* DESCRIPTION:
 * Function returns an iterator to the next element in order in the bst.
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * where       - iterator of the part of the bst to get the next from.
 *      
 * RETURN:
 * iterator to the next element in order.
 * time: ??? (fill on your own)
 * space: O(1)
 */
bst_iter_t BSTIterNext(bst_iter_t where);

/* DESCRIPTION:
 * Function returns an iterator to the previous element in order in the bst.
 * passing an invalid iterator would result in undefined behaviour.
 *
 * PARAMS:
 * where         - iterator of the part of the bst to get the previous of.
 *      
 * RETURN:
 * iterator to the previous element in order.
 * time: ??? (fill on your own)
 * space: O(1)
 */
bst_iter_t BSTIterPrev(bst_iter_t where);

/* DESCRIPTION:
 * Function returns an iterator to the smallest element in order of the bst.
 * passing an empty bst would result in undefined behaviour.
 *
 * PARAMS:
 * bst         - pointer to a bst 
 *      
 * RETURN:
 * iterator to the smallest element of the bst.
 * 
 * time: O(log n), worst O(n)
 * space: O(1)
 */
bst_iter_t BSTBegin(const bst_t *tree);

/* DESCRIPTION:
 * Function returns an iterator to the biggest element in order of the bst..
 *
 * PARAMS:
 * bst         - pointer to a bst 
 *      
 * RETURN:
 * iterator to the End of the bst.
 * 
 * time: O(1)
 * space: O(1)
 */
bst_iter_t BSTEnd(const bst_t *tree);

/* DESCRIPTION:
 * Function compares between two iterators.
 * passing invalid iterators would result in undefined behaviour.
 * 
 * PARAMS:
 * iter_one         - first iterator to compare 
 * iter_two         - second iterator to compare
 * 
 * RETURN:
 * 1 when iterators are identical, 0 otherwise.
 * 
 * time: O(1)
 * space: O(1)
 */
int BSTIsEqual(bst_iter_t iter_one, bst_iter_t iter_two);

#endif /* __BST_H__ */

