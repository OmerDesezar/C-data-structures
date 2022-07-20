/*
    team: OL125-126    
    version: 1.0

*/
#ifndef _AVL_H_
#define _AVL_H_

#include <stddef.h> /* size_t */

typedef int (*action_func_t)(void *data, void *param);
typedef int (*cmp_func_t)(const void *data1, const void *data2);

typedef struct avl avl_t;

typedef enum traverse
{
    PRE_ORDER,
    POST_ORDER,
    IN_ORDER
}traverse_t;

/* DESCRIPTION:
 * Function creates an empty avl
 *
 * PARAMS:
 * cmp_fun - pointer to the compare function
 *         
 * RETURN:
 * Returns a pointer to the created avl
 *
 * COMPLEXITY:
 * time: best - O(1)
 * space: O(1)
 */
avl_t *AVLCreate(cmp_func_t cmp_func);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given avl.
 * passing an invalid avl pointer would result in undefined behaviour
 * This function should be used when finshing using the avl.
 *
 * PARAMS:
 * tree - pointer to the avl to be destroyed
 *         
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void AVLDestroy(avl_t *tree);

/* DESCRIPTION:
 * Function checks whether the avl is empty
 *
 * PARAMS:
 * tree - pointer to the tree to check if empty
 *         
 * RETURN:
 * 1 if the avl is empty or 0 otherwise
 *
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
int AVLIsEmpty(const avl_t *tree);

/* DESCRIPTION:
 * Function returns the data of the given element after inserting it to the given avl.
 * passing an invalid tree would result in undefined behaviour.
 *
 * PARAMS:
 * tree - avl to insert the data to
 * data - the data to insert
 *      
 * RETURN:															
 * 0 for success, 1 if fail.
 *
 * COMPLEXITY:
 * average time: O(log n)
 * space: O(1)
 */
int AVLInsert(avl_t *tree, void *data);

/* DESCRIPTION:
 * Function removes node for the tree based on the given key from the avl.
 * passing an invalid node would result in undefined behaviour.
 *
 * PARAMS:
 * key - key to find node to remove.
 * tree - avl tree to remove from.
 *      
 * RETURN:
 * void 
 *
 * COMPLEXITY: 
 * time: O(log n)
 * space: O(1)
 */
void AVLRemove(avl_t *tree, const void *key);

/* DESCRIPTION:
 * Function finds elements base on the return value of is_match function ,in a given range.
 * passing invalid nodeators would result in undefined behaviour.
 *
 * PARAMS:
 * key - key to find node in avl.
 * tree - avl tree to find key in.
 *         
 * RETURN:
 * node to the found data. NULL if not found.
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */
void *AVLFind(const avl_t *tree, const void *key);

/* DESCRIPTION:
 * Function returns the number of elements in the avl.
 * passing an invalid avl would result in undefined behaviour.
 *
 * PARAMS:
 * avl - pointer to a avl  
 *      
 * RETURN:
 * number of elements
 *
 * COMPLEXITY:
 * time: O(n) 
 * space: O(1)
 */
size_t AVLSize(const avl_t *tree);

/* DESCRIPTION:
 * Function performs an action on each element in the given tree.
 * passing an invalid node would result in undefined behaviour.
 *
 * PARAMS:
 * tree         - pointer to the avl tree
 * action_func  - function pointer to an action to perform on a node
 * param        - element for action function
 * type         - enum type of traversal (PRE/POST/IN ORDER)
 *      
 * RETURN:
 * 0 if success 1 else.
 * time: O(n)
 * space: O(1)
 */
int AVLForEach(avl_t *tree, action_func_t action_func, void *param, traverse_t type); 

/* DESCRIPTION:
 * Function checks the tree's height.
 *
 * PARAMS:
 * tree - pointer to the tree to check height
 *         
 * RETURN:
 * The tree's height - leaf height is 1.
 *
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
size_t AVLHeight(const avl_t *tree);

#endif /* __AVL_H__ */
