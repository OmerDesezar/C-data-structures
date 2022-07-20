#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */


typedef struct block_header vsa_t;

/* DESCRIPTION:
 * Function initiates an allocator for a specified memory pool.
 * Passing an invalid position may cause undefined behaviour.
 *
 * PARAMS:
 * pool_start - pointer to the memory pool.
 * pool_size  - size of memory pool in bytes.
 *
 * RETURN:
 * A pointer to the initialized allocator.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
vsa_t *VsaInit(void *pool_start, size_t pool_size);

/* DESCRIPTION:
 * Function allocates a block of memory of size requested from the allocator.
 *
 * PARAMS:
 * memory_pool - the pointer to the allocator to request a block from.
 * block_size - size of block requested.
 *
 * RETURN:
 * Pointer to the requested memory block. Null if alloc failed.
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
void *VsaAlloc(vsa_t *memory_pool, size_t block_size);

/* DESCRIPTION:
 * Function frees a block of memory that has been previously allocated from the allocator.
 *
 * PARAMS:
 * block_ptr - the pointer to the block to be freed.
 *         
 * RETURN:
 * void.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void VsaFree(void *block_ptr);

/* DESCRIPTION:
 * Function return largest chunk avaliable to alloc in the allocator.
 *
 * PARAMS:
 * memory_pool - pointer to the allocator to find largest chunk of
 *         
 * RETURN:
 * largest chunk avaliable to alloc in the allocator
 *
 * COMPLEXITY:
 * time: O(n)
 * space: O(1)
 */
size_t VsaLargestChunkAvaliable(vsa_t *memory_pool);

#endif /* __VSA_H__ */

