#include <stdio.h> /* printf */

#include "priorityq.h"

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
	priority_q_t *queue = PriorityQCreate(SortBySize);
	
	if(NULL != queue)
	{
		printf("PriorityQCreate working!                             V\n");
	}
	else
	{
		printf("PriorityQCreate NOT working!                         X\n");
	}
	
	PriorityQDestroy(queue);
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
	
	priority_q_t *queue = PriorityQCreate(SortBySize);
	
	PriorityQEnqueue(queue, (void*)&x);
	PriorityQEnqueue(queue, (void*)&y);
	PriorityQEnqueue(queue, (void*)&between);
	
	third = *(int*) PriorityQDequeue(queue);
	second = *(int*) PriorityQDequeue(queue);
	first = *(int*) PriorityQDequeue(queue);
	
	if((3 == first) && (4 == second) && (5 == third))
	{
		printf("PriorityQEnqueue & PriorityQDequeue working!         V\n");
	}
	else
	{
		printf("PriorityQEnqueue & PriorityQDequeue NOT working!     X\n");
	}
	
	PriorityQDestroy(queue);
}

static void TestSizeAndEmpty()
{	
	int x = 3;
	int y = 5;
	int before = -1;
	int after = -1;
	int empty = -1;
	int not_empty = -1;
	
	priority_q_t *queue = PriorityQCreate(SortBySize);
	
	before = PriorityQSize(queue);
	empty = PriorityQIsEmpty(queue);
	
	PriorityQEnqueue(queue, (void*)&x);
	PriorityQEnqueue(queue, (void*)&y);
	
	after = PriorityQSize(queue);
	not_empty = PriorityQIsEmpty(queue);
	
	if(0 == before && 2 == after)
	{
		printf("PriorityQSize working!                               V\n");
	}
	else
	{
		printf("PriorityQSize NOT working!                           X\n");
	}
	
	if(1 == empty && 0 == not_empty)
	{
		printf("PriorityQIsEmpty working!                            V\n");
	}
	else
	{
		printf("PriorityQIsEmpty NOT working!                        X\n");
	}
	
	PriorityQDestroy(queue);
}

static void TestErase()
{
	int x = 3;
	int y = 4;
	int z = 5;
	int to_div = 2;
	
	priority_q_t *queue = PriorityQCreate(SortBySize);
	
	PriorityQEnqueue(queue, (void*)&x);
	PriorityQEnqueue(queue, (void*)&y);
	PriorityQEnqueue(queue, (void*)&z);
	
	y = *(int*) PriorityQErase(queue, DivideMatch, (void*)&to_div);
	z = *(int*) PriorityQDequeue(queue);
	x = *(int*) PriorityQDequeue(queue);

	if((3 == x) && (4 == y) && (5 == z))
	{
		printf("PriorityQErase working!                              V\n");
	}
	else
	{
		printf("PriorityQErase NOT working!                          X\n");
	}
	
	PriorityQDestroy(queue);
}

static void TestPeek()
{
	int x = 3;
	int y = 4;
	int z = 5;
	int peeked = -1;
	
	priority_q_t *queue = PriorityQCreate(SortBySize);
	
	PriorityQEnqueue(queue, (void*)&y);
	PriorityQEnqueue(queue, (void*)&z);
	PriorityQEnqueue(queue, (void*)&x);
	
	peeked = *(int*)PriorityQPeek(queue);
	
	if(5 == peeked)
	{
		printf("PriorityQPeek working!                               V\n");
	}
	else
	{
		printf("PriorityQPeek NOT working!                           X\n");
	}
	
	PriorityQDestroy(queue);
}

static void TestClear()
{	
	int x = 3;
	int y = 4;
	int z = 5;
	int empty = -1;
	int not_empty = -1;
	
	priority_q_t *queue = PriorityQCreate(SortBySize);
	
	PriorityQEnqueue(queue, (void*)&x);
	PriorityQEnqueue(queue, (void*)&y);
	PriorityQEnqueue(queue, (void*)&z);
	
	not_empty = PriorityQIsEmpty(queue);
	
	PriorityQClear(queue);
	
	empty = PriorityQIsEmpty(queue);
	
	if(1 == empty && 0 == not_empty)
	{
		printf("PriorityQClear working!                              V\n");
	}
	else
	{
		printf("PriorityQClear NOT working!                          X\n");
	}
	
	
	PriorityQDestroy(queue);
}

static int SortBySize(const void *data, const void *data2)
{
	return (*(int*)data - *(int*)data2);
}

static int DivideMatch(const void *data, const void *param)
{
    return (0 == (*(int *)data % *(int *)param));
}


