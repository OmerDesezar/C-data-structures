#include <stdio.h> /* printf */
#include <string.h> /* memcmp */

#include "../include/stack.h"

void TestAllFuncs();

int main()
{
	TestAllFuncs();
	return (0);
}

void TestAllFuncs()
{
	int x = 5;
	int x2;
	char y = 'g';
	char y2;
	char z[10] = "omer";
	char *z2;
	stack_ptr_t stack = StackCreate(10, 10);
	if(10 == StackGetCapacity(stack))
	{
		printf("good\n");
	}
	StackPush(stack, &x);
	StackPush(stack, &y);
	StackPush(stack, &z);
	if(3 == StackGetSize(stack))
	{
		printf("better\n");
	}
	z2 = (char*)StackPop(stack);
	y2 = *(char*)StackPop(stack);
	x2 = *(int*)StackPop(stack);
	if(StackIsEmpty(stack))
	{
		printf("exellent\n");
	}
	if(x == x2)
	{
		printf("nice\n");
	}
	if(y == y2)
	{
		printf("nice2\n");
	}
	StackDestroy(stack);
}









