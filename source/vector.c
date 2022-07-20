/*######################### LIBRARIES & MACROS #############################*/

#include <stdlib.h> /* malloc, realloc, free */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "../include/vector.h"
#define GROWTH_FACTOR 2
#define SUCCESS 0
#define FAIL 1

/*############################# DEFINITIONS ###############################*/

struct vector
{
	char *base;
	size_t element_size;
	size_t max_element_count;
	size_t element_count;
};

/* Approved by Yedidia */

vector_ptr_t VectorCreate(size_t initial_capacity, size_t element_size)
{
	vector_ptr_t vector;
	vector = (vector_ptr_t)malloc(sizeof(vector_t));

	if (NULL == vector)
	{
		return (NULL);
	}

	vector->base = (char *)malloc(initial_capacity * element_size);

	if (NULL == vector->base)
	{
		return (NULL);
	}

	vector->element_size = element_size;
	vector->max_element_count = initial_capacity;
	vector->element_count = 0;

	return (vector);
}

void VectorDestroy(vector_ptr_t vector)
{
	assert(NULL != vector);

	free(vector->base);
	vector->base = NULL;
	free(vector);
	vector = NULL;
}

int VectorPushBack(vector_ptr_t vector, const void *element_to_push)
{
	int status = SUCCESS;
	assert(NULL != vector);
	assert(NULL != element_to_push);

	if (vector->element_count >= (vector->max_element_count - 1))
	{
		status = VectorReserve(vector, (vector->max_element_count * GROWTH_FACTOR));
	}

	if (SUCCESS == status)
	{
		memcpy(vector->base + (vector->element_count * vector->element_size),
			   element_to_push, vector->element_size);
		++vector->element_count;
	}

	return (status);
}

void *VectorPopBack(vector_ptr_t vector)
{
	assert(NULL != vector);
	assert(0 < vector->element_count);

	--vector->element_count;

	if (vector->element_count < vector->max_element_count / (GROWTH_FACTOR * 2))
	{
		VectorReserve(vector, (vector->max_element_count / GROWTH_FACTOR));
	}

	return ((void *)(vector->base + (vector->element_count * vector->element_size)));
}

void *VectorAccessAt(const vector_ptr_t vector, size_t index)
{
	assert(NULL != vector);
	assert(index < vector->element_count);
	return ((void *)(vector->base + (index * vector->element_size)));
}

int VectorReserve(vector_ptr_t vector, size_t new_capacity)
{
	assert(NULL != vector);
	vector->base = (char *)realloc(vector->base, (new_capacity * vector->element_size));
	if (NULL == vector->base)
	{
		return (FAIL);
	}
	vector->max_element_count = new_capacity;
	return (SUCCESS);
}

size_t VectorGetSize(const vector_ptr_t vector)
{
	assert(NULL != vector);
	return (vector->element_count);
}

size_t VectorGetCapacity(const vector_ptr_t vector)
{
	assert(NULL != vector);
	return (vector->max_element_count);
}

int VectorIsEmpty(const vector_ptr_t vector)
{
	assert(NULL != vector);
	return (0 == vector->element_count);
}

int VectorShrinkToFit(vector_ptr_t vector)
{
	int status = SUCCESS;
	assert(NULL != vector);
	status = VectorReserve(vector, (vector->element_count + 1));
	return (status);
}
