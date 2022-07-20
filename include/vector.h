/*
    team: OL125-126    
    version: 1.0
    date: 28/04/2022
*/
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

struct vector;

typedef struct vector *vector_ptr_t;
typedef struct vector vector_t;

/*
 * Recommended struct impl:
 *
 * struct vector
 * {
 *		char *base;
 *		size_t size_of_element;
 *		size_t capacity;
 *		size_t size;
 * }
 *
 */


/* DESCRIPTION:
 * Function creates an empty vector of specified capacity, with total storage 
 * space being limited by implementation defined constant and system limits
 *
 * PARAMS:
 * initial_capacity - initial capacity in elements
 * element_size 	- size of each element to be stored in the vector
 *         
 * RETURN:
 * Returns a pointer to the new vector, or NULL on error
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: capacity
 */
vector_ptr_t VectorCreate(size_t initial_capacity, size_t element_size);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given vector,
 * but not on any passed elements
 * passing an invalid vector pointer would result in undefined behaviour
 *
 * PARAMS:
 * vector - pointer to the vector to be destroyed
 *         
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void VectorDestroy(vector_ptr_t vector);

/* DESCRIPTION:
 * Function pushes given element into the vector
 * when trying to fill up to a full vector, it will be expanded if possible
 * passing an invalid vector pointer would result in undefined behaviour
 *
 * PARAMS:
 * vector 			- pointer to the vector to push into
 * element_to_push  - pointer to the element to push
 *         
 * RETURN:
 * status
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: best - O(1), worst - O(n)
 */
int VectorPushBack(vector_ptr_t vector, const void *element_to_push);

/* DESCRIPTION:
 * Function removes the top element of the vector and returns it
 * trying to pop an empty vector will result in undefined behavior
 * in case the vector is significantly shrunk, its capacity will be truncated
 * passing an invalid vector pointer would result in undefined behaviour
 *
 * PARAMS:
 * vector - pointer to the vector to pop from
 *         
 * RETURN:
 * pointer to the stored variable
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: best - O(1), worst - O(n)
 */
void *VectorPopBack(vector_ptr_t vector);

/* DESCRIPTION:
 * Function accesses the vector at the specified index.
 * passing an invalid vector pointer would result in undefined behaviour
 * passing an out of bound index would result in undefined behaviour
 * accessing an empty vector would result in undefined behaviour
 *
 * PARAMS:
 * vector - pointer to the vector to pop from
 * index - the index of the element to be accessed
 *         
 * RETURN:
 * Returns a pointer to the new place inside the vector
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void *VectorAccessAt(const vector_ptr_t vector, size_t index);

/* DESCRIPTION:
 * Changes the current capacity to at least the specified capacity
 * passing an invalid vector pointer would result in undefined behaviour
 * passing a capacity smaller than the current vector's size would result in
 * undefined behaviour
 *
 * PARAMS:
 * vector 	  - pointer to the vector to pop from
 * to_reserve - the amount of requested elements
 *         
 * RETURN:
 * status
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: O(n)
 */

int VectorReserve(vector_ptr_t vector, size_t new_capacity);

/* DESCRIPTION:
 * Function gets the size of the given vector
 * passing an invalid vector pointer would result in undefined behaviour
 *
 * PARAMS:
 * vector         - pointer to the vector to get the size of
 *         
 * RETURN:
 * the size of the given vector
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
size_t VectorGetSize(const vector_ptr_t vector);

/* DESCRIPTION:
 * Function gets the capacity of the given vector
 * passing an invalid vector pointer would result in undefined behaviour
 *
 * PARAMS:
 * vector         - pointer to the vector to get the capacity of
 *         
 * RETURN:
 * the capacity of the given vector
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
size_t VectorGetCapacity(const vector_ptr_t vector);

/* DESCRIPTION:
 * Function checks whether our vector is empty
 * passing an invalid vector pointer would result in undefined behaviour
 *
 * PARAMS:
 * vector - pointer to the vector to check if empty
 *         
 * RETURN:
 * 1 if the vector is empty or 0 otherwise
 *
 * COMPLEXITY:
 * O(1)
 */
int VectorIsEmpty(const vector_ptr_t vector);

/* DESCRIPTION:
 * Function shrinks the vector to the current occupied size
 * passing an invalid vector pointer would result in undefined behaviour
 *
 * PARAMS:
 * vector - pointer to the vector to pop from
 *         
 * RETURN:
 * status
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: best - O(1), worst - O(n)
 */
int VectorShrinkToFit(vector_ptr_t vector);

#endif /* __VECTOR_H__ */
