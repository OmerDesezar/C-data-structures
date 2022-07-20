/*
    team: OL125-126    
    version: 2.0.0

*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /*size_t*/

struct queue;

typedef struct queue *queue_ptr_t;
typedef struct queue queue_t;

typedef enum queue_status
{
	SUCCESS,
	FAIL
} q_status_t;

/*
 *
 * struct queue
 * {
 *	slist_ptr_t slist;
 *	size_t size;
 * }
 *
 *
 * DESCRIPTION:
 * Function creates an empty queue
 *
 * PARAMS:
 * none
 *         
 * RETURN:
 * Returns a pointer to the new queue
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: O(1)
 */
queue_ptr_t QCreate(void);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given queue
 * passing an invalid queue pointer would result in undefined behaviour
 *
 * PARAMS:
 * queue - pointer to the queue to be destroyed
 *         
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void QDestroy(queue_ptr_t queue);

/* DESCRIPTION:
 * Function checks whether the given queue is empty
 * passing an invalid queue pointer would result in undefined behaviour
 *
 * PARAMS:
 * queue - pointer to the queue to be checked
 *         
 * RETURN:
 * 1 if empty, 0 otherwise
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
int QIsEmpty(const queue_ptr_t queue);

/* DESCRIPTION:
 * Function adds the element to the end of the queue 
 * passing an invalid queue would result in undefined behaviour
 * passing an invalid element would result in undefined behaviour
 * passing an empty queue should result in undefined behavior
 * PARAMS:
 * queue   - the queue to insert the element into
 * element - the element to insert
 *      
 * RETURN:															
 * status indicating success or a predefined error 
 *
 * COMPLEXITY:
 * time: O(1), worst - indeterminable ?
 * space: O(1)
 */ 
q_status_t QEnQueue(queue_ptr_t queue, const void *element);

/* DESCRIPTION:
 * Function removes the element at the front of the queue and returns it
 * passing an invalid queue would result in undefined behaviour
 *
 * PARAMS:
 * queue - the queue to remove the element from
 *      
 * RETURN:															
 * a void pointer containing the removed queue element 
 *
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
void QDeQueue(queue_ptr_t queue);

/* DESCRIPTION:
 * Function returns the element at the head of the queue without removing it
 * passing an invalid queue would result in undefined behaviour
 * passing an empty queue should result in undefined behavior
 *
 * PARAMS:
 * queue - the queue to get the element from
 *      
 * RETURN:															
 * a void pointer containing the peeked queue element 
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void *QPeek(const queue_ptr_t queue);

/* DESCRIPTION:
 * Function returns the number of elements on the queue.
 * passing an invalid queue would result in undefined behaviour.
 *
 * PARAMS:
 * queue - pointer to the queue to count from
 *      
 * RETURN:
 * number of elements in the queue
 *
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
size_t QGetSize(const queue_ptr_t queue);

/* DESCRIPTION:
 * Function Append qdest and qsrc into qdest and empty qsrc.
 * passing an invalid qdest would result in undefined behaviour.
 * passing an invalid qsrc would result in undefined behaviour.
 * 
 *	PARAMS:
 * qdest -  pointer to the queue to append to.
 * qsrc - pointer to the queue to append from.
 *
 * RETURN:
 * void
 *	
 * COMPLEXITY:
 * time: O(1) 
 * space: O(1)
 */
void QAppend(queue_ptr_t qdest, queue_ptr_t qsrc);

#endif /* __QUEUE_H__ */

