#include <stdio.h> /* printf */

#include "pq_heap.h"

static void TestAllFuncs();
static void TestCreate();
static void TestDestroy();
static void TestClear();
static void TestEnqueueNDequeue();
static void TestSizeAndEmpty();
static void TestErase();
static void TestPeek();

static int SortBySize(const void *data, const void *data2);
static int DivideMatch(const void *data, const void *param);

int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestCreate();
	TestEnqueueNDequeue();
	TestSizeAndEmpty();
	TestErase();
	TestPeek();
	TestClear();
	TestDestroy();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
	pq_heap_t *queue = PQHeapCreate(SortBySize);

	if (NULL != queue)
	{
		printf("PQHeapCreate working!                                V\n");
	}
	else
	{
		printf("PQHeapCreate NOT working!                            X\n");
	}

	PQHeapDestroy(queue);
}

static void TestDestroy()
{
	printf("*Run vlg to test SortedListDestroy*\n");
}

static void TestEnqueueNDequeue()
{
	int x = 3;
	int between = 4;
	int y = 5;
	int first = -1;
	int second = -1;
	int third = -1;

	pq_heap_t *queue = PQHeapCreate(SortBySize);
	PQHeapEnqueue(queue, &x);
	PQHeapEnqueue(queue, &y);
	PQHeapEnqueue(queue, &between);

	third = *(int *)PQHeapPeek(queue);
	PQHeapDequeue(queue);
	second = *(int *)PQHeapPeek(queue);
	PQHeapDequeue(queue);
	first = *(int *)PQHeapPeek(queue);
	PQHeapDequeue(queue);

	if ((3 == first) && (4 == second) && (5 == third))
	{
		printf("PQHeapEnqueue & PQHeapDequeue working!               V\n");
	}
	else
	{
		printf("PQHeapEnqueue & PQHeapDequeue NOT working!           X\n");
	}

	PQHeapDestroy(queue);
}

static void TestSizeAndEmpty()
{
	int x = 3;
	int y = 5;
	int before = -1;
	int after = -1;
	int empty = -1;
	int not_empty = -1;

	pq_heap_t *queue = PQHeapCreate(SortBySize);

	before = PQHeapSize(queue);
	empty = PQHeapIsEmpty(queue);

	PQHeapEnqueue(queue, (void *)&x);
	PQHeapEnqueue(queue, (void *)&y);

	after = PQHeapSize(queue);
	not_empty = PQHeapIsEmpty(queue);

	if (0 == before && 2 == after)
	{
		printf("PQHeapSize working!                                  V\n");
	}
	else
	{
		printf("PQHeapSize NOT working!                              X\n");
	}

	if (1 == empty && 0 == not_empty)
	{
		printf("PQHeapIsEmpty working!                               V\n");
	}
	else
	{
		printf("PQHeapIsEmpty NOT working!                           X\n");
	}

	PQHeapDestroy(queue);
}

static void TestErase()
{
	int x = 3;
	int y = 4;
	int z = 5;
	int to_div = 2;

	pq_heap_t *queue = PQHeapCreate(SortBySize);

	PQHeapEnqueue(queue, (void *)&x);
	PQHeapEnqueue(queue, (void *)&y);
	PQHeapEnqueue(queue, (void *)&z);

	y = *(int *)PQHeapErase(queue, DivideMatch, (void *)&to_div);

	if (4 == y)
	{
		printf("PQHeapErase working!                                 V\n");
	}
	else
	{
		printf("PQHeapErase NOT working!                             X\n");
	}

	PQHeapDestroy(queue);
}

static void TestPeek()
{
	int x = 3;
	int y = 4;
	int z = 5;
	int peeked = -1;

	pq_heap_t *queue = PQHeapCreate(SortBySize);

	PQHeapEnqueue(queue, (void *)&y);
	PQHeapEnqueue(queue, (void *)&z);
	PQHeapEnqueue(queue, (void *)&x);

	peeked = *(int *)PQHeapPeek(queue);

	if (5 == peeked)
	{
		printf("PQHeapPeek working!                                  V\n");
	}
	else
	{
		printf("PQHeapPeek NOT working!                              X\n");
	}

	PQHeapDestroy(queue);
}

static void TestClear()
{
	int x = 3;
	int y = 4;
	int z = 5;
	int empty = -1;
	int not_empty = -1;

	pq_heap_t *queue = PQHeapCreate(SortBySize);

	PQHeapEnqueue(queue, (void *)&x);
	PQHeapEnqueue(queue, (void *)&y);
	PQHeapEnqueue(queue, (void *)&z);

	not_empty = PQHeapIsEmpty(queue);

	PQHeapClear(queue);

	empty = PQHeapIsEmpty(queue);

	if (1 == empty && 0 == not_empty)
	{
		printf("PQHeapClear working!                                 V\n");
	}
	else
	{
		printf("PQHeapClear NOT working!                             X\n");
	}

	PQHeapDestroy(queue);
}

static int SortBySize(const void *data, const void *data2)
{
	return (*(int *)data - *(int *)data2);
}

static int DivideMatch(const void *data, const void *param)
{
	return (0 == (*(int *)data % *(int *)param));
}
