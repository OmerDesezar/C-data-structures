#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include "../include/vector.h"

static void Red();
static void Blue();
static void Purple();
static void Green();
static void Yellow();
static void Reset();
static void PushRand (vector_ptr_t vector);
static void PopRand (vector_ptr_t vector);

int main(void)
{
	vector_ptr_t vector = VectorCreate(2 ,sizeof(int));
	
	Yellow();
	printf ("********** CREATE VECTOR OF INTEGERS **********\n");
	printf ("Vector created, size: %lu, capacity: %lu\n", VectorGetSize(vector),
				VectorGetCapacity(vector));
	printf ("Is empty: %d\n", VectorIsEmpty(vector));
	
	Red();
	printf ("********** START PUSHING INTEGERS **********\n");
	PushRand(vector);
	
	Green();
	printf ("********** ACCESSING ELEMENTS AT INDEXES **********\n");
	printf ("Access at %d: value is %d\n", 0, *(int *)VectorAccessAt(vector, 0));
	printf ("Access at %d: value is %d\n", 5, *(int *)VectorAccessAt(vector, 5));
	
	Blue();
	printf ("********** START POPPING **********\n");
	PopRand(vector);
	
	Red();
	printf ("********** PUSH SOME MORE **********\n");
	PushRand(vector);
	
	Purple();
	printf ("Vector's capacity is now: %ld\n", VectorGetCapacity(vector));
	printf ("********** SHRINK TO FIT **********\n");
	VectorShrinkToFit(vector);
	printf ("After Shrinkage:\n");
	printf ("Vector's capacity is now: %ld\n", VectorGetCapacity(vector));
	VectorDestroy(vector);
	Reset();
	return (0);
}

static void Red()
{
	printf("\033[1;31m");
}

static void Blue()
{
	printf("\033[1;34m");
}

static void Purple()
{
	printf("\033[1;35m");
}

static void Green()
{
	printf("\033[1;32m");
}

static void Yellow()
{
	printf ("\033[1;33m");
}

static void Reset()
{
	printf("\033[0m");
}

static void PushRand (vector_ptr_t vector)
{
	size_t i = 0;
	int temp = 100;
	for (i = 0; i < 40; ++i)
	{
		VectorPushBack(vector, &temp);
		printf ("\tValue pushed, at vector[%ld]: %d\n", i, temp);
		printf ("\tsize: %lu, capacity: %lu\n", VectorGetSize(vector),
				VectorGetCapacity(vector));
		printf ("\tIs empty: %d\n", VectorIsEmpty(vector));
		++temp;	
	}
}

static void PopRand (vector_ptr_t vector)
{
	size_t i = 0;
	for (i = 0; i < 40; ++i)
	{
		printf ("\tValue popped, at vector[%ld]: %d\n", VectorGetSize(vector),
				*(int *)VectorPopBack(vector));
		printf ("\tsize: %lu, capacity: %lu\n", VectorGetSize(vector),
				VectorGetCapacity(vector));
		printf ("\tIs empty: %d\n", VectorIsEmpty(vector));
	
	}
}

