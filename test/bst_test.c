#include <stdio.h> /* printf */

#include "bst.h"

static int IntCompare(const void *data1, const void *data2);
static int IntAdd(void *data, void *param);

static void TestAllFuncs();
static void TestCreate();
static void TestSizeAndEmpty();
static void TestInsert();
static void TestGetData();
static void TestRemove();
static void TestIterFuncs();
static void TestDestroy();
static void TestFind();
static void TestForEach();


int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestCreate();
	TestInsert();
	TestRemove();
	TestGetData();
	TestIterFuncs();
	TestSizeAndEmpty();
	TestFind();
	TestForEach();
	TestDestroy();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
	bst_t *tree = BSTCreate(IntCompare);
	
	if(NULL != tree)
	{
		printf("BSTCreate working!                                   V\n");
	}
	else
	{
		printf("BSTCreate NOT working!                               X\n");
	}
	
	BSTDestroy(tree);
}

static void TestDestroy()
{
	printf("*Run vlg to test BSTDestroy*\n");
}

static void TestInsert()
{
	int a = 6, b = 16, c = 4, d = 2, e = 8, f = 12, g = 10, h = 20, i = 18, j = 14;
	bst_iter_t runner = NULL;
	int is_working = 1;
	int z = 0;

	bst_t *tree = BSTCreate(IntCompare);

	BSTInsert(tree, &a);
	BSTInsert(tree, &b);
	BSTInsert(tree, &c);
	BSTInsert(tree, &d);
	BSTInsert(tree, &e);
	BSTInsert(tree, &f);
	BSTInsert(tree, &g);
	BSTInsert(tree, &h);
	BSTInsert(tree, &i);
	BSTInsert(tree, &j);
	runner = BSTBegin(tree);
	
	for(z = 2; z <= 20; z+=2)
	{
		if(z != *(int*)BSTGetData(runner))
		{
			is_working = 0;
			break;
		}
		runner = BSTIterNext(runner);
	}

	if(is_working)
	{
		printf("BSTInsert working!                                   V\n");
	}
	else
	{
		printf("BSTInsert NOT working!                               X\n");
	}
	
	BSTDestroy(tree);
}

static void TestRemove()
{
	int a = 5, b = 3, c = 4;
	size_t size_before = -1, size_after = -1;

	bst_t *tree = BSTCreate(IntCompare);

	BSTInsert(tree, &a);
	BSTInsert(tree, &b);
	BSTInsert(tree, &c);
	
	size_before = BSTSize(tree);
	
	BSTRemove(BSTBegin(tree));
	BSTRemove(BSTBegin(tree));
	
	size_after = BSTSize(tree);
	
	if((2 == size_before - size_after) && 
	5 == *(int *)BSTGetData(BSTBegin(tree)))
	{
		printf("BSTRemove working!                                   V\n");
	}
	else
	{
		printf("BSTRemove NOT working!                               X\n");
	}
	
	BSTDestroy(tree);
}

static void TestSizeAndEmpty()
{	
	int a = 3, b = 5;
	size_t size_before = 0, size_after = 0;
	int empty = -1, not_empty = -1;
	
	bst_t *tree = BSTCreate(IntCompare);
	
	size_before = BSTSize(tree);
	empty = BSTIsEmpty(tree);
	
	BSTInsert(tree, (void*)&a);
	BSTInsert(tree, (void*)&b);
	
	size_after = BSTSize(tree);
	not_empty = BSTIsEmpty(tree);
	
	if(0 == size_before && 2 == size_after)
	{
		printf("BSTSize working!                                     V\n");
	}
	else
	{
		printf("BSTSize NOT working!                                 X\n");
	}
	
	if(1 == empty && 0 == not_empty)
	{
		printf("BSTIsEmpty working!                                  V\n");
	}
	else
	{
		printf("BSTIsEmpty NOT working!                              X\n");
	}
	
	BSTDestroy(tree);
}

static void TestGetData()
{
	int a = 5, b = 3, c = 4;
	bst_iter_t runner = NULL;
	
	bst_t *tree = BSTCreate(IntCompare);

	BSTInsert(tree, &a);
	BSTInsert(tree, &b);
	BSTInsert(tree, &c);
	
	runner = BSTIterNext(BSTBegin(tree));
	
	if(3 == *(int*)BSTGetData(BSTBegin(tree)) && 4 == *(int *)BSTGetData(runner))
	{
		printf("BSTGetData working!                                  V\n");
	}
	else
	{
		printf("BSTGetData NOT working!                              X\n");
	}
	
	BSTDestroy(tree);
}

static void TestIterFuncs()
{
	int a = 5, b = 3, c = 4, d = 2, e = 8, f = 12, g = 10, h = 9, i = 11, j = 14;
	bst_iter_t runner = NULL, runner2 = NULL;
	int first, second, third;

	bst_t *tree = BSTCreate(IntCompare);

	BSTInsert(tree, &a);
	BSTInsert(tree, &b);
	BSTInsert(tree, &c);
	BSTInsert(tree, &d);
	BSTInsert(tree, &e);
	BSTInsert(tree, &f);
	BSTInsert(tree, &g);
	BSTInsert(tree, &h);
	BSTInsert(tree, &i);
	BSTInsert(tree, &j);
	
	runner = BSTBegin(tree);
	runner = BSTIterNext(BSTIterNext(BSTIterNext(
	BSTIterNext(BSTIterNext(runner)))));
	first = *(int *)BSTGetData(runner);

	runner = BSTIterPrev(BSTIterNext(BSTIterNext(
	BSTIterNext(BSTIterNext(runner)))));
	second = *(int *)BSTGetData(runner);

	runner = BSTIterPrev(BSTIterPrev(BSTIterNext(runner)));
	third = *(int *)BSTGetData(runner);

	runner2 = BSTIterNext(BSTIterNext(BSTIterNext(
	BSTIterNext(BSTIterNext(BSTIterNext(BSTBegin(tree)))))));
	runner = BSTIterPrev(runner);

	if(2 == *(int *)BSTGetData(BSTBegin(tree)))
	{
		printf("BSTBegin working!                                    V\n");
	}
	else
	{
		printf("BSTBegin NOT working!                                X\n");
	}
	if(NULL == (bst_t*)BSTGetData(BSTEnd(tree)))
	{
		printf("BSTEnd working!                                      V\n");
	}
	else
	{
		printf("BSTEnd NOT working!                                  X\n");
	}
	if(9 == first)
	{
		printf("BSTIterNext working!                                 V\n");
	}
	else
	{
		printf("BSTIterNext NOT working!                             X\n");
	}
	if(12 == second && 11 == third )
	{
		printf("BSTIterPrev working!                                 V\n");
	}
	else
	{
		printf("BSTIterPrev NOT working!                             X\n");
	}
	if(BSTIsEqual(runner2, runner))
	{
		printf("BSTIsEqual working!                                  V\n");
	}
	else
	{
		printf("BSTIsEqual NOT working!                              X\n");
	}
	
	BSTDestroy(tree);
}


static void TestFind()
{
	int a = 5, b = 9, c = 3, d = 7;
	int to_find = 5;
	int not_there = 12;

	bst_iter_t not_found;
	bst_iter_t found_iter;
	
	bst_t *tree = BSTCreate(IntCompare);
	
	BSTInsert(tree, (void*)&a);
	BSTInsert(tree, (void*)&b);
	BSTInsert(tree, (void*)&c);
	BSTInsert(tree, (void*)&d);
	
	found_iter = BSTFind(tree, (void *)&to_find);
	not_found = BSTFind(tree, (void *)&not_there);
	
	if(5 == *(int *)BSTGetData(found_iter) && BSTEnd(tree) == not_found)
    {
    	printf("BSTFind working!                                     V\n");
	}
	else
	{
		printf("BSTFind NOT working!                                 X\n");
	}
	
	BSTDestroy(tree);
}

static void TestForEach()
{
	int a = 5, b = 9, c = 3, d = 7;
	int num_to_add = 10;
	
	bst_t *tree = BSTCreate(IntCompare);
	
	BSTInsert(tree, (void*)&a);
	BSTInsert(tree, (void*)&b);
	BSTInsert(tree, (void*)&c);
	BSTInsert(tree, (void*)&d);
	
	BSTForEach(BSTBegin(tree), BSTEnd(tree), IntAdd, (void *)&num_to_add);
	
	if(13 == *(int*)BSTGetData(BSTBegin(tree)) && 
		19 == *(int*)BSTGetData(BSTIterPrev(BSTEnd(tree))))
    {
    	printf("BSTForEach working!                                  V\n");
	}
	else
	{
		printf("BSTForEach NOT working!                              X\n");
	}
	
	BSTDestroy(tree);
}



static int IntCompare(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

int IntAdd(void *data, void *param)
{
	*(int *)data += *(int *)param;

	return 0;
}

