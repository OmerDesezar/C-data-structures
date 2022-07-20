/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "vector.h"
#include "heap.h"

#define LEFT 1
#define RIGHT 2
#define INIT_CAP 10
#define GROWTH_FACTOR 2
#define POINTER_SIZE 8
#define SUCCESS 0
#define FAIL 1
#define TRUE 1
#define FALSE 0

/*====================== STRUCT & FUNCTION DECLATARIONS =======================*/

struct binary_heap
{
    vector_t *vector;
    cmp_func_t cmp;
};

static size_t GetParentIndex(size_t);
static size_t GetLastIndex(vector_t *);
static size_t GetChildIndex(size_t, int);
static void *GetElement(bin_heap_t *, size_t);
static void HeapifyUpRec(bin_heap_t *, size_t);
static void SwapElements(vector_t *, int, int);
static void HeapifyDownRec(bin_heap_t *, size_t);
static int ReturnTrue(const void *, const void *);
static void SwapWithLastElement(vector_t *, size_t);
static int UseCompareFunc(bin_heap_t *, size_t, size_t);
static int UseIsMatchFunc(bin_heap_t *, heap_is_match_t, size_t, void *);

/*=========================== FUNCTION DEFINITION ===========================*/

bin_heap_t *BinHeapCreate(cmp_func_t cmp_func)
{
    bin_heap_t *heap = NULL;
    assert(NULL != cmp_func);
    heap = (bin_heap_t *)malloc(sizeof(bin_heap_t));
    if (NULL != heap)
    {
        heap->vector = VectorCreate(INIT_CAP, POINTER_SIZE);
        if (NULL == heap->vector)
        {
            free(heap);
            return (NULL);
        }
        heap->cmp = cmp_func;
    }
    return (heap);
}

void BinHeapDestroy(bin_heap_t *heap)
{
    assert(NULL != heap);
    VectorDestroy(heap->vector);
    free(heap);
}

int BinHeapPush(bin_heap_t *heap, const void *data)
{
    assert(NULL != heap);
    if (SUCCESS == VectorPushBack(heap->vector, &data))
    {
        HeapifyUpRec(heap, GetLastIndex(heap->vector));
        return (SUCCESS);
    }
    return (FAIL);
}

void BinHeapPop(bin_heap_t *heap)
{
    assert(NULL != heap);
    BinHeapRemove(heap, ReturnTrue, 0);
}

void *BinHeapPeek(bin_heap_t *heap)
{
    assert(NULL != heap);
    assert(0 < VectorGetSize(heap->vector));
    return (GetElement(heap, 0));
}

void *BinHeapRemove(bin_heap_t *heap, heap_is_match_t is_match, void *param)
{
    size_t to_remove = 0, last_index = 0;
    void *rtn = NULL;
    assert(NULL != heap);
    assert(NULL != is_match);
    last_index = GetLastIndex(heap->vector);
    for (; to_remove <= last_index && TRUE != UseIsMatchFunc(heap, is_match, to_remove, param); ++to_remove)
        ;
    if (to_remove <= last_index)
    {
        rtn = GetElement(heap, to_remove);
        SwapWithLastElement(heap->vector, to_remove);
        VectorPopBack(heap->vector);
        if (to_remove < last_index)
        {
            HeapifyUpRec(heap, to_remove);
            HeapifyDownRec(heap, to_remove);
        }
    }
    return (rtn);
}

size_t BinHeapSize(const bin_heap_t *heap)
{
    assert(NULL != heap);
    return (VectorGetSize(heap->vector));
}

int BinHeapIsEmpty(const bin_heap_t *heap)
{
    assert(NULL != heap);
    return (VectorIsEmpty(heap->vector));
}

static size_t GetChildIndex(size_t index, int side)
{
    return ((2 * index) + side);
}

static size_t GetParentIndex(size_t index)
{
    return ((0 == index) ? (index) : ((index - 1) / 2));
}

static size_t GetLastIndex(vector_t *vector)
{
    return ((0 == VectorGetSize(vector)) ? 0 : VectorGetSize(vector) - 1);
}

static void SwapElements(vector_t *vector, int first, int second)
{
    void **ptr1 = (void **)VectorAccessAt(vector, first);
    void **ptr2 = (void **)VectorAccessAt(vector, second);
    void *tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

static void SwapWithLastElement(vector_t *vector, size_t index)
{
    SwapElements(vector, index, GetLastIndex(vector));
}

static void HeapifyUpRec(bin_heap_t *heap, size_t index)
{
    if (0 < UseCompareFunc(heap, index, GetParentIndex(index)))
    {
        SwapElements(heap->vector, index, GetParentIndex(index));
        HeapifyUpRec(heap, GetParentIndex(index));
    }
}

static void HeapifyDownRec(bin_heap_t *heap, size_t index)
{
    size_t last_index = GetLastIndex(heap->vector);
    size_t l_child_index = GetChildIndex(index, LEFT);
    size_t r_child_index = GetChildIndex(index, RIGHT);
    size_t biggest_index = index;
    if (l_child_index <= last_index && (0 < UseCompareFunc(heap, l_child_index, biggest_index)))
    {
        biggest_index = l_child_index;
    }
    if (r_child_index <= last_index && (0 < UseCompareFunc(heap, r_child_index, biggest_index)))
    {
        biggest_index = r_child_index;
    }
    if (biggest_index != index)
    {
        SwapElements(heap->vector, index, biggest_index);
        HeapifyDownRec(heap, biggest_index);
    }
}

static int UseCompareFunc(bin_heap_t *heap, size_t index1, size_t index2)
{
    return (heap->cmp(GetElement(heap, index1), GetElement(heap, index2)));
}

static int UseIsMatchFunc(bin_heap_t *heap, heap_is_match_t is_match, size_t index, void *data)
{
    return (is_match(GetElement(heap, index), data));
}

static void *GetElement(bin_heap_t *bin_heap, size_t index)
{
    return (*(void **)VectorAccessAt(((bin_heap_t *)bin_heap)->vector, index));
}

static int ReturnTrue(const void *data1, const void *data2)
{
    (void)data1;
    (void)data2;
    return (TRUE);
}