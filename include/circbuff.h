/*
    team: OL125-126    
    version: 1.0.0
    date: 04.05.22
*/

#ifndef __CIRCBUFF_H__
#define __CIRCBUFF_H__

#include <stddef.h> /* size_t */
#include <unistd.h> /* ssize_t */

struct circbuff;

typedef struct circbuff *circbuff_ptr_t;

/*
 *
 * struct circbuff
 * {
 *  size_t read_index;
 *  size_t write_index;
 *  size_t capacity;
 *	char buff[1];
 * }
 *
 *
 * DESCRIPTION:
 * Function creates an empty buffer with a user defined size
 *
 * PARAMS:
 * capacity     - capacity of buffer
 *        
 * RETURN:
 * Returns a pointer to the new buffer
 *
 * COMPLEXITY:
 * time: best - O(1), worst - indeterminable
 * space: O(1)
 */
circbuff_ptr_t CircBuffCreate(size_t capacity);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given buffer
 * passing an invalid buffer pointer would result in undefined behaviour
 *
 * PARAMS:
 * buffer - pointer to the buffer to be destroyed
 *         
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void CircBuffDestroy(circbuff_ptr_t buffer);

/* DESCRIPTION:
 * Function checks whether the given buffer is empty
 * passing an invalid buffer pointer would result in undefined behaviour
 *
 * PARAMS:
 * buffer - pointer to the buffer to be checked
 *         
 * RETURN:
 * 1 if empty, 0 otherwise
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
int CircBuffIsEmpty(const circbuff_ptr_t buffer);

/* DESCRIPTION:
 * Function reads the next in line element in the buffer 
 * passing an empty buffer to read from would result in undefined behaviour
 * passing an invalid buffer to write to would result in undefined behaviour
 *
 * PARAMS:
 * buffer             - the buffer to read from
 * num_of_bytes       - the number of bytes to read
 * to_write_to        - the buffer to write into
 * 
 * RETURN:															
 * number of bytes that have been read on success,
 * -1 when failed to read from 
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */ 
ssize_t CircBuffRead(circbuff_ptr_t buffer, void *to_write_to, size_t num_of_bytes);

/* DESCRIPTION:
 * Function writes to the buffer at the next available space
 * passing a full buffer would result in overwriting data
 * passing an invalid buffer would result in undefined behaviour
 * passing an invalid read from would result in undefined behaviour
 *
 * PARAMS:
 * buffer         - the buffer to write to
 * to_read_from   - the buffer to read from
 * num_of_bytes   - the number of bytes to write
 *      
 * RETURN:															
 * number of bytes that have been written on success,
 * -1 when failed to write to 
 * 
 * COMPLEXITY:
 * time: O(n) 
 * space: O(1)
 */
ssize_t CircBuffWrite(circbuff_ptr_t buffer, const void *to_read_from, size_t num_of_bytes);

/* DESCRIPTION:
 * Function returns the number of bytes currently in use.
 * passing an invalid buffer would result in undefined behaviour.
 *
 * PARAMS:
 * buffer - pointer to the buffer to get the current number of bytes in use.
 *    
 * RETURN:
 * current number of bytes in use.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
size_t CircBuffSize(const circbuff_ptr_t buffer);

/* DESCRIPTION:
 * Function returns the number of bytes not in use.
 * passing an invalid buffer would result in undefined behaviour.
 *
 * PARAMS:
 * buffer - pointer to the buffer to get the current free space
 *      
 * RETURN:
 * number of bytes unused on the buffer
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
size_t CircBuffFreeSpace(const circbuff_ptr_t buffer);

#endif /* __CIRCBUFF_H__ */

