/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "../include/stack.h"

#define MAX_CAPACITY_IN_BYTES 1048576
#define MIN2(a, b) (((a) > (b)) ? (b) : (a))

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct stack
{
	char *top;
	size_t element_size;
	size_t max_element_count;
	size_t element_count;
};

/* Approved by Itamar */
stack_ptr_t StackCreate(size_t max_element_count, size_t element_size)
{
	stack_ptr_t stack;
	max_element_count = MIN2(max_element_count, 
			MAX_CAPACITY_IN_BYTES / element_size);
	stack = (stack_ptr_t) malloc(sizeof(stack_t) + 
			(max_element_count * element_size));
	if (NULL == stack)
	{
		return NULL;
	}
	stack->top = (char*)stack + sizeof(stack_t);
	stack->max_element_count = max_element_count;
	stack->element_size = element_size;
	stack->element_count = 0;
	
	return (stack);
}

void StackDestroy(stack_ptr_t stack)
{
	free(stack);
}

void StackPush(stack_ptr_t stack, const void *element_to_push)
{
	assert(stack);
	assert(stack->element_count < stack->max_element_count);
	
	memcpy(stack->top, element_to_push, stack->element_size);
	stack->top += stack->element_size;
	++stack->element_count;
}

void *StackPop(stack_ptr_t stack)
{
	assert(stack);
	assert(0 < stack->element_count);
	
	stack->top -= stack->element_size;
	--stack->element_count;
	return ((void*)stack->top);
}

int StackIsEmpty(const stack_ptr_t stack)
{
	assert(stack);
	return (0 == stack->element_count);
}

size_t StackGetSize(const stack_ptr_t stack)
{
	assert(stack);
	return (stack->element_count);
}

size_t StackGetCapacity(const stack_ptr_t stack)
{
	assert(stack);
	return (stack->max_element_count);
}

void *StackPeek(const stack_ptr_t stack)
{
	assert(stack);
	return ((void*)(stack->top - stack->element_size));
}









