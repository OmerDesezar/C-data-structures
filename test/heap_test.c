#include <stdio.h> /* printf */
#include "heap.h"

static void TestAllFuncs();
static void TestCreate();
static void TestDestroy();
static void TestPush();
static void TestPop();
static void TestPeek();
static void TestRemove();
static void TestSizeEmpty();
static int IntCompare(const void *num1, const void *num2);
static int IntMatch(const void *num1, const void *num2);

int main()
{
    TestAllFuncs();
    return (0);
}

static void TestAllFuncs()
{
    printf("     ~START OF TEST FUNCTION~ \n");
    TestCreate();
    TestPush();
    TestPop();
    TestPeek();
    TestSizeEmpty();
    TestRemove();
    TestDestroy();
    printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
    bin_heap_t *heap = BinHeapCreate(IntCompare);

    if (NULL != heap)
    {
        printf("BinHeapCreate working!                               V\n");
    }
    else
    {
        printf("BinHeapCreate NOT working!                           X\n");
    }

    BinHeapDestroy(heap);
}

static void TestDestroy()
{
    printf("*Run vlg to test BinHeapDestroy*\n");
}

static void TestPush()
{
    int a = 8, b = 2, c = 10, e = 11, d = 15;
    int size_before = -1;
    int size_after = -1;
    bin_heap_t *heap = BinHeapCreate(IntCompare);

    size_before = BinHeapSize(heap);

    BinHeapPush(heap, &a);
    BinHeapPush(heap, &b);
    BinHeapPush(heap, &c);
    BinHeapPush(heap, &d);
    BinHeapPush(heap, &e);

    size_after = BinHeapSize(heap);
    if (5 == size_after - size_before && 15 == *(int *)BinHeapPeek(heap))
    {
        printf("BinHeapPush working!                                 V\n");
    }
    else
    {
        printf("BinHeapPush NOT working!                             X\n");
    }

    BinHeapDestroy(heap);
}

static void TestPop()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int size_before = -1;
    int size_after = -1;
    bin_heap_t *heap = BinHeapCreate(IntCompare);

    BinHeapPush(heap, &a);
    BinHeapPush(heap, &b);
    BinHeapPush(heap, &c);
    BinHeapPush(heap, &d);
    BinHeapPush(heap, &e);

    size_before = BinHeapSize(heap);
    BinHeapPop(heap);
    BinHeapPop(heap);
    size_after = BinHeapSize(heap);

    if (2 == size_before - size_after && 10 == *(int *)BinHeapPeek(heap))
    {
        printf("BinHeapPop working!                                  V\n");
    }
    else
    {
        printf("BinHeapPop NOT working!                              X\n");
    }

    BinHeapDestroy(heap);
}

static void TestPeek()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int peek1 = -1;
    int peek2 = -1;
    bin_heap_t *heap = BinHeapCreate(IntCompare);

    BinHeapPush(heap, &a);
    BinHeapPush(heap, &b);
    BinHeapPush(heap, &c);
    peek1 = *(int *)BinHeapPeek(heap);
    BinHeapPush(heap, &d);
    peek2 = *(int *)BinHeapPeek(heap);
    BinHeapPush(heap, &e);

    if (10 == peek1 && 15 == peek2)
    {
        printf("BinHeapPeek working!                                 V\n");
    }
    else
    {
        printf("BinHeapPeek NOT working!                             X\n");
    }

    BinHeapDestroy(heap);
}

static void TestSizeEmpty()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int size_before = -1;
    int size_after = -1;
    int empty = -1;
    int not_empty = -1;
    bin_heap_t *heap = BinHeapCreate(IntCompare);

    size_before = BinHeapSize(heap);
    empty = BinHeapIsEmpty(heap);

    BinHeapPush(heap, &a);
    BinHeapPush(heap, &b);
    BinHeapPush(heap, &c);
    BinHeapPush(heap, &d);
    BinHeapPush(heap, &e);

    size_after = BinHeapSize(heap);
    not_empty = BinHeapIsEmpty(heap);

    if (0 == size_before && 5 == size_after)
    {
        printf("BinHeapSize working!                                 V\n");
    }
    else
    {
        printf("BinHeapSize NOT working!                             X\n");
    }

    if (1 == empty && 0 == not_empty)
    {
        printf("BinHeapIsEmpty working!                              V\n");
    }
    else
    {
        printf("BinHeapIsEmpty NOT working!                          X\n");
    }

    BinHeapDestroy(heap);
}

static void TestRemove()
{
    int a = 8, b = 2, c = 10, d = 15, e = 11;
    int to_find = 10;
    int to_not_find = 144;
    int size_before = -1;
    int size_after = -1;
    int removed1 = -1;
    bin_heap_t *heap = BinHeapCreate(IntCompare);

    BinHeapPush(heap, &a);
    BinHeapPush(heap, &b);
    BinHeapPush(heap, &c);
    BinHeapPush(heap, &d);
    BinHeapPush(heap, &e);

    size_before = BinHeapSize(heap);

    removed1 = *(int *)BinHeapRemove(heap, IntMatch, &to_find);
    BinHeapRemove(heap, IntMatch, &to_not_find);

    size_after = BinHeapSize(heap);

    if (5 == size_before && 4 == size_after && 10 == removed1 && NULL == BinHeapRemove(heap, IntMatch, &to_not_find))
    {
        printf("BinHeapRemove working!                               V\n");
    }
    else
    {
        printf("BinHeapRemove NOT working!                           X\n");
    }

    BinHeapDestroy(heap);
}

static int IntCompare(const void *num1, const void *num2)
{
    return (*(int *)num1 - *(int *)num2);
}

static int IntMatch(const void *num1, const void *num2)
{
    return (*(int *)num1 == *(int *)num2);
}