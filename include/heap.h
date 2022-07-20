/*
    team: OL125-126
    version: 1.0

*/

#include <stddef.h> /* size_t */


typedef int (*heap_is_match_t)(const void *data, const void *param);
typedef int (*cmp_func_t)(const void *key1, const void *key2);

typedef struct binary_heap bin_heap_t;


/* DESCRIPTION:
 * Function creates an empty binary heap
 *
 * PARAMS:
 * cmp_fun - pointer to the comapre function
 *
 * RETURN:
 * Returns a pointer to the created binary heap
 *
 * COMPLEXITY:
 * time: best - O(1)
 * space: O(1)
 */
bin_heap_t *BinHeapCreate(cmp_func_t cmp_fun);

/* DESCRIPTION:
 * Function destroys and performs cleanup on the given binary heap.
 * passing an invalid binary heap would result in undefined behaviour
 * This function should be used when finshing using the binary heap.
 *
 * PARAMS:
 * binary heap - pointer to the binary heap to be destroyed
 *
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void BinHeapDestroy(bin_heap_t *bin_heap);

/* DESCRIPTION:
 * Function checks whether the binary heap is empty
 *
 * PARAMS:
 * binary heap - pointer to the binary heap to check if empty
 *
 * RETURN:
 * 1 if the binary heap is empty or 0 otherwise
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
int BinHeapIsEmpty(const bin_heap_t *bin_heap);

/* DESCRIPTION:
 * Function returns the data after pushing it to the given binary heap.
 * passing an invalid binary heap would result in undefined behaviour.
 *
 * PARAMS:
 * binary heap - binary heap to push the data to
 * data - the data to push
 *
 * RETURN:
 * 0 for SUCCESS, 1 for FAIL
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */

int BinHeapPush(bin_heap_t *bin_heap, const void *data);

/* DESCRIPTION:
 * Function pops the first element from the given binary heap.
 * passing an invalid heap would result in undefined behaviour.
 *
 * PARAMS:
 * bin_heap - binary heap to pop.
 *
 * RETURN:
 * void.
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */
void BinHeapPop(bin_heap_t *bin_heap);

/* DESCRIPTION:
 * Function returns the first element from the given binary heap.
 * passing an invalid heap would result in undefined behaviour.
 *
 * PARAMS:
 * bin_heap - binary heap to pop.
 *
 * RETURN:
 * pointer to the data.
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
void *BinHeapPeek(bin_heap_t *bin_heap);

/* DESCRIPTION:
 * Function pops data from the given binary heap based on the given key and is_match function.
 * passing an invalid heap would result in undefined behaviour.
 *
 * PARAMS:
 * bin_heap - binary heap to remove from.
 * is_match - Function to find the correct data.
 * param    - The element to remove
 *
 * RETURN:
 * pointer to the data that has been removed. If not found, will return NULL.
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */
void *BinHeapRemove(bin_heap_t *bin_heap, heap_is_match_t is_match, void *param);

/* DESCRIPTION:
 * Function returns the number of elements in the binary heap.
 * passing an invalid binary heap would result in undefined behaviour.
 *
 * PARAMS:
 * binary heap - pointer to a binary heap
 *
 * RETURN:
 * number of elements
 *
 * COMPLEXITY:
 * time: O(1)
 * space: O(1)
 */
size_t BinHeapSize(const bin_heap_t *bin_heap);
