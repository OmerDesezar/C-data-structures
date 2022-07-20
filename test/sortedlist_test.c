#include <stdio.h> /* printf */

#include "sortedlist.h"

static void TestAllFuncs();
static void TestCreate();
static void TestSizeAndEmpty();
static void TestInsertBefore();
static void TestGetData();
static void TestRemove();
static void TestIterFuncs();
static void TestPops();
static void TestDestroy();
static void TestFind();
static void TestFindIf();
static void TestForEach();
static void TestMerge();

static int SortBySize(const void *data, const void *data2);
static int DivideMatch(const void *data, const void *param);
static int AddToNum(void* ptr, void* param);

int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestCreate();
	TestSizeAndEmpty();
	TestInsertBefore();
	TestGetData();
	TestRemove();
	TestPops();
	TestIterFuncs();
	TestFind();
	TestFindIf();
	TestForEach();
	TestMerge();
	TestDestroy();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
	int x = 3;
	int y = 5;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	if(NULL != list)
	{
		printf("SortedListCreate working!                            V\n");
	}
	else
	{
		printf("SortedListCreate NOT working!                        X\n");
	}
	
	SortedListInsert(list, (void*)&x);
	SortedListInsert(list, (void*)&y);
	
	SortedListDestroy(list);
}

static void TestDestroy()
{
	printf("*Run vlg to test SortedListDestroy*\n");
}

static void TestSizeAndEmpty()
{	
	int x = 3;
	int y = 5;
	int before = -1;
	int after = -1;
	int empty = -1;
	int not_empty = -1;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	before = SortedListSize(list);
	empty = SortedListIsEmpty(list);
	
	SortedListInsert(list, (void*)&x);
	SortedListInsert(list, (void*)&y);
	
	after = SortedListSize(list);
	not_empty = SortedListIsEmpty(list);
	
	if(0 == before && 2 == after)
	{
		printf("SortedListSize working!                              V\n");
	}
	else
	{
		printf("SortedListSize NOT working!                          X\n");
	}
	
	if(1 == empty && 0 == not_empty)
	{
		printf("SortedListIsEmpty working!                           V\n");
	}
	else
	{
		printf("SortedListIsEmpty NOT working!                       X\n");
	}
	
	SortedListDestroy(list);
}

static void TestInsertBefore()
{
	int x = 3;
	int between = 4;
	int y = 5;
	sorted_list_iter_t runner;
	int first = -1;
	int second = -1;
	int third = -1;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&x);
	SortedListInsert(list, (void*)&y);
	SortedListInsert(list, (void*)&between);
	
	runner = SortedListBegin(list);
	first = *(int*)SortedListGetData(runner);
	runner = SortedListIterNext(runner);
	second = *(int*)SortedListGetData(runner);
	runner = SortedListIterNext(runner);
	third = *(int*)SortedListGetData(runner);
	
	if((3 == first) && (4 == second) && (5 == third))
	{
		printf("SortedListInsert working!                            V\n");
	}
	else
	{
		printf("SortedListInsert NOT working!                        X\n");
	}
	
	SortedListDestroy(list);
}


static void TestGetData()
{
	int x = 3;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&x);
	
	if(3 == *(int*)SortedListGetData(SortedListBegin(list)))
	{
		printf("SortedListGetData working!                           V\n");
	}
	else
	{
		printf("SortedListGetData NOT working!                       X\n");
	}
	
	SortedListDestroy(list);
}

static void TestRemove()
{
	int x = 7;
	int y = 3;
	int z = 5;
	int size_before = -1;
	int size_after = -1;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&x);
	SortedListInsert(list, (void*)&y);
	SortedListInsert(list, (void*)&z);
	
	size_before = SortedListSize(list);
	
	SortedListRemove(SortedListBegin(list));
	
	size_after = SortedListSize(list);
	
	if((1 == size_before - size_after) && 
	5 == *(int*)SortedListGetData(SortedListBegin(list)))
	{
		printf("SortedListRemove working!                            V\n");
	}
	else
	{
		printf("SortedListRemove NOT working!                        X\n");
	}
	
	SortedListDestroy(list);
}


static void TestPops()
{
	int a = 5;
	int b = 9;
	int c = 3;
	int d = 7;
	int pop_from_back = -1;
	int pop_from_front = -1;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&a);
	SortedListInsert(list, (void*)&b);
	SortedListInsert(list, (void*)&c);
	SortedListInsert(list, (void*)&d);
	
	pop_from_back = *(int*)SortedListPopBack(list);
	pop_from_front = *(int*)SortedListPopFront(list);
	
	if(b == pop_from_back)
	{
		printf("SortedListPopBack working!                           V\n");
	}
	else
	{
		printf("SortedListPopBack NOT working!                       X\n");
	}
	
	if(c == pop_from_front)
	{
		printf("SortedListPopFront working!                          V\n");
	}
	else
	{
		printf("SortedListPopFront NOT working!                      X\n");
	}
	
	SortedListDestroy(list);
}

static void TestIterFuncs()
{
	int a = 5;
	int b = 9;
	int c = 3;
	int d = 7;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&a);
	SortedListInsert(list, (void*)&b);
	SortedListInsert(list, (void*)&c);
	SortedListInsert(list, (void*)&d);
	
	if(3 == *(int*)SortedListGetData(SortedListBegin(list)))
	{
		printf("SortedListBegin working!                             V\n");
	}
	else
	{
		printf("SortedListBegin NOT working!                         X\n");
	}
	
	if(NULL == (dlist_t*)SortedListGetData(SortedListEnd(list)))
	{
		printf("SortedListEnd working!                               V\n");
	}
	else
	{
		printf("SortedListEnd NOT working!                           X\n");
	}
	
	if(5 == *(int*)SortedListGetData(SortedListIterNext(SortedListBegin(list))))
	{
		printf("SortedListIterNext working!                          V\n");
	}
	else
	{
		printf("SortedListIterNext NOT working!                      X\n");
	}
	
	if(9 == *(int*)SortedListGetData(SortedListIterPrev(SortedListEnd(list))))
	{
		printf("SortedListIterPrev working!                          V\n");
	}
	else
	{
		printf("SortedListIterPrev NOT working!                      X\n");
	}
	
	
	if(SortedListIsSameIter(
	SortedListIterPrev(SortedListIterPrev(SortedListEnd(list))),
	SortedListIterNext(SortedListIterNext(SortedListBegin(list)))))
	{
		printf("SortedListIsSameIter working!                        V\n");
	}
	else
	{
		printf("SortedListIsSameIter NOT working!                    X\n");
	}
	
	SortedListDestroy(list);
}


static void TestFind()
{
	int a = 5;
	int b = 9;
	int c = 3;
	int d = 7;
	int to_find = 5;
	sorted_list_iter_t found_iter;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&a);
	SortedListInsert(list, (void*)&b);
	SortedListInsert(list, (void*)&c);
	SortedListInsert(list, (void*)&d);
	
	found_iter = SortedListFind(
	SortedListBegin(list), SortedListEnd(list), list, (void*)&to_find);

	if(5 == *(int *)SortedListGetData(found_iter))
    {
    	printf("SortedListFind working!                              V\n");
	}
	else
	{
		printf("SortedListFind NOT working!                          X\n");
	}
	
	SortedListDestroy(list);
}


static void TestFindIf()
{
	int a = 5;
	int b = 9;
	int c = 11;
	int d = 7;
	int to_div = 3;
	sorted_list_iter_t found_iter;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&a);
	SortedListInsert(list, (void*)&b);
	SortedListInsert(list, (void*)&c);
	SortedListInsert(list, (void*)&d);
	
	found_iter = SortedListFindIf(
	SortedListBegin(list), SortedListEnd(list), DivideMatch, (void*)&to_div);

	if(9 == *(int *)SortedListGetData(found_iter))
    {
    	printf("SortedListFindIf working!                            V\n");
	}
	else
	{
		printf("SortedListFindIf NOT working!                        X\n");
	}
	
	SortedListDestroy(list);
}


static void TestForEach()
{
	int a = 5;
	int b = 9;
	int c = 3;
	int d = 7;
	int num_to_add = 100;
	
	sorted_list_t *list = SortedListCreate(SortBySize);
	
	SortedListInsert(list, (void*)&a);
	SortedListInsert(list, (void*)&b);
	SortedListInsert(list, (void*)&c);
	SortedListInsert(list, (void*)&d);
	
	SortedListForEach(
	SortedListBegin(list),SortedListEnd(list), AddToNum, (void*)&num_to_add);
	
	if(103 == *(int*)SortedListGetData(SortedListBegin(list)) && 
	109 == *(int*)SortedListGetData(SortedListIterPrev(SortedListEnd(list))))
    {
    	printf("SortedListForEach working!                           V\n");
	}
	else
	{
		printf("SortedListForEach NOT working!                       X\n");
	}

	SortedListDestroy(list);
}

static void TestMerge()
{
	int a = 1;
	int b = 3;
	int c = 5;
	int d = 7;
	int e = 2;
	int f = 4;
	int g = 6;
	int h = 8;
	int i = 9;
	int j = 10;
	int k = 11;
	int l = 12;
	int status = 0;
	int counter = 1;
	sorted_list_iter_t runner;
	
	sorted_list_t *dest_list = SortedListCreate(SortBySize);
	sorted_list_t *src_list = SortedListCreate(SortBySize);
	
	SortedListInsert(dest_list, (void*)&a);
	SortedListInsert(dest_list, (void*)&b);
	SortedListInsert(dest_list, (void*)&c);
	SortedListInsert(dest_list, (void*)&d);
	
	SortedListInsert(src_list, (void*)&e);
	SortedListInsert(src_list, (void*)&f);
	SortedListInsert(src_list, (void*)&g);
	SortedListInsert(src_list, (void*)&h);
	SortedListInsert(src_list, (void*)&i);
	SortedListInsert(src_list, (void*)&j);
	SortedListInsert(src_list, (void*)&k);
	SortedListInsert(src_list, (void*)&l);
	
	SortedListMerge(dest_list, src_list);

	runner = SortedListBegin(dest_list);
	while(!SortedListIsSameIter(runner, SortedListEnd(dest_list)))
	{
		if(counter != *(int*)SortedListGetData(runner))
		{
			status = 1;
		}
		runner = SortedListIterNext(runner);
		++counter;
	}
	
	if(0 != SortedListSize(src_list))
	{
		status = 1;
	}
	
	if(status == 0)
    {
    	printf("SortedListMerge working!                             V\n");
	}
	else
	{
		printf("SortedListMerge NOT working!                         X\n");
	}
	SortedListDestroy(dest_list);
	SortedListDestroy(src_list);
}


static int SortBySize(const void *data, const void *data2)
{
	return (*(int*)data - *(int*)data2);
}

static int DivideMatch(const void *data, const void *param)
{
    return (0 == (*(int *)data % *(int *)param));
}

static int AddToNum(void* ptr, void* param)
{
	*(int*)ptr += *(int*)param;
	return (0);
}


