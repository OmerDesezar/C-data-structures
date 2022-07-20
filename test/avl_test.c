#include <stdio.h> /* printf */

#include "avl.h"

static int IntCompare(const void *data1, const void *data2);
static int IntAdd(void *data, void *param);

static void TestAllFuncs();
static void TestCreate();
static void TestSizeEmptyHeight();
static void TestInsert();
static void TestRemove();
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
	TestSizeEmptyHeight();
	TestFind();
	TestForEach();
	TestDestroy();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
	avl_t *tree = AVLCreate(IntCompare);
	
	if(NULL != tree)
	{
		printf("AVLCreate working!                                   V\n");
	}
	else
	{
		printf("AVLCreate NOT working!                               X\n");
	}
	
	AVLDestroy(tree);
}

static void TestDestroy()
{
	printf("*Run vlg to test AVLDestroy*\n");
}

static void TestInsert()
{
	int a = 6, b = 16, c = 4, d = 2, e = 8, f = 12, g = 10, h = 20, i = 18, j = 14;
	int size_before = -1;
	int size_after = -1;
	avl_t *tree = AVLCreate(IntCompare);
	
	size_before = AVLSize(tree);
	
	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	AVLInsert(tree, &e);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &h);
	AVLInsert(tree, &i);
	AVLInsert(tree, &j);
	
	size_after = AVLSize(tree);
	
	if(0 == size_before && 10 == size_after)
	{
		printf("AVLInsert working!                                   V\n");
	}
	else
	{
		printf("AVLInsert NOT working!                               X\n");
	}
	
	AVLDestroy(tree);
}

static void TestRemove()
{
	int a = 5, b = 3, c = 4, d = 10;
	size_t size_before = -1, size_after = -1;

	avl_t *tree = AVLCreate(IntCompare);

	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	
	size_before = AVLSize(tree);
	
	AVLRemove(tree, &b);
	AVLRemove(tree, &d);
	
	size_after = AVLSize(tree);
	
	if(2 == size_before - size_after)
	{
		printf("AVLRemove working!                                   V\n");
	}
	else
	{
		printf("AVLRemove NOT working!                               X\n");
	}
	
	AVLDestroy(tree);
}

static void TestSizeEmptyHeight()
{	
	int a = 4, b = 6, c = 2, d = 3, e = 1, f = 0;
	size_t size_before = 0, size_after = 0;
	size_t height_before = 0, height_after = 0;
	int empty = -1, not_empty = -1;
	
	avl_t *tree = AVLCreate(IntCompare);
	
	size_before = AVLSize(tree);
	empty = AVLIsEmpty(tree);
	
	AVLInsert(tree, (void*)&a);
	
	height_before = AVLHeight(tree);
	
	AVLInsert(tree, (void*)&b);
	AVLInsert(tree, (void*)&c);
	AVLInsert(tree, (void*)&d);
	AVLInsert(tree, (void*)&e);
	AVLInsert(tree, (void*)&f);
	
	height_after = AVLHeight(tree);
	
	size_after = AVLSize(tree);
	not_empty = AVLIsEmpty(tree);
	
	if(0 == size_before && 6 == size_after)
	{
		printf("AVLSize working!                                     V\n");
	}
	else
	{
		printf("AVLSize NOT working!                                 X\n");
	}
	
	if(1 == empty && 0 == not_empty)
	{
		printf("AVLIsEmpty working!                                  V\n");
	}
	else
	{
		printf("AVLIsEmpty NOT working!                              X\n");
	}
	
	if(1 == height_before && 3 == height_after)
	{
		printf("AVLHeight working!                                   V\n");
	}
	else
	{
		printf("AVLHeight NOT working!                               X\n");
	}
	
	AVLDestroy(tree);
}

static void TestFind()
{
	int a = 5, b = 9, c = 3, d = 7;
	int to_find = 5;
	int not_there = 12;
	
	avl_t *tree = AVLCreate(IntCompare);
	
	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	
	if(to_find == *(int*)AVLFind(tree, &to_find) && NULL == AVLFind(tree, &not_there))
    {
    	printf("AVLFind working!                                     V\n");
	}
	else
	{
		printf("AVLFind NOT working!                                 X\n");
	}
	
	AVLDestroy(tree);
}

static void TestForEach()
{
	int a = 5, b = 9, c = 3, d = 7;
	int e = 3;
	int num_to_add = 10;
	
	avl_t *tree = AVLCreate(IntCompare);
	
	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	
	AVLForEach(tree, IntAdd, &num_to_add, POST_ORDER);
	
	if(13 == *(int*)AVLFind(tree, &c) && NULL == AVLFind(tree, &e))
    {
    	printf("AVLForEach working!                                  V\n");
	}
	else
	{
		printf("AVLForEach NOT working!                              X\n");
	}
	
	AVLDestroy(tree);
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

