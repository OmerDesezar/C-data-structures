#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include "fsa.h"

static void TestAllFuncs();
static void TestSuggestSize();
static void TestInit();
static void TestAlloc();
static void TestFree();
static void TestCountFree();

int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestSuggestSize();
	TestInit();
	TestAlloc();
	TestFree();
	TestCountFree();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestSuggestSize()
{
	size_t block_size1 = 15;
	size_t block_size2 = 16;
	size_t block_size3 = 17;
	size_t num_of_blocks = 4;
	size_t should_suggest1 = 80;
	size_t should_suggest2 = 112;
	size_t suggested1 = FsaSuggestSize(num_of_blocks, block_size1);
	size_t suggested2 = FsaSuggestSize(num_of_blocks, block_size2);
	size_t suggested3 = FsaSuggestSize(num_of_blocks, block_size3);
	
	if(suggested1 == should_suggest1 && 
		suggested2 == should_suggest1 && 
		suggested3 == should_suggest2)
	{
		printf("FsaSuggestSize working!                              V\n");
	}
	else
	{
		printf("FsaSuggestSize NOT working!                          X\n");
	}
}

static void TestInit()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FsaSuggestSize(num_of_blocks, block_size);
	size_t counter = 0;
	fsa_t *fsa = NULL;
	
	void* pool = malloc(pool_size);
	
	fsa = FsaInit(pool, pool_size, block_size);
	
	while(NULL != FsaAlloc(fsa))
	{
		++counter;
	}
	
	if(num_of_blocks == counter)
	{
		printf("FsaInit working!                                     V\n");
	}
	else
	{
		printf("FsaInit NOT working!                                 X\n");
	}
	
	free(pool);
}

static void TestAlloc()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FsaSuggestSize(num_of_blocks, block_size);
	size_t addresses[4] = {0};
	fsa_t *fsa = NULL;
	size_t i = 0;
	int is_working = 1;
	
	void* pool = malloc(pool_size);
	
	fsa = FsaInit(pool, pool_size, block_size);
	
	for(; i < num_of_blocks; ++i)
	{
		addresses[i] = (size_t)FsaAlloc(fsa);
	}
	
	if(NULL != FsaAlloc(fsa))
	{
		is_working = 0;
	}
	
	for(i = 0; i < (num_of_blocks - 1); ++i)
	{
		if(block_size != addresses[i+1] - addresses[i])
		{
			is_working = 0;
			break;
		}
	}
	
	if(1 == is_working)
	{
		printf("FsaAlloc working!                                    V\n");
	}
	else
	{
		printf("FsaAlloc NOT working!                                X\n");
	}
	
	free(pool);
}

static void TestFree()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FsaSuggestSize(num_of_blocks, block_size);
	void* allocated[4];
	fsa_t *fsa = NULL;
	size_t i = 0;
	int is_working = 1;
	
	void* pool = malloc(pool_size);
	
	fsa = FsaInit(pool, pool_size, block_size);
	
	for(; i < num_of_blocks; ++i)
	{
		allocated[i] = FsaAlloc(fsa);
	}
	
	for(i = 0; i < num_of_blocks; ++i)
	{
		FsaFree(fsa, allocated[i]);
	}
	
	for(i = 0; i < num_of_blocks; ++i)
	{
		if(NULL == FsaAlloc(fsa))
		{
			is_working = 0;
		}
	}
	
	if(1 == is_working)
	{
		printf("FsaFree working!                                     V\n");
	}
	else
	{
		printf("FsaFree NOT working!                                 X\n");
	}
	
	free(pool);
}

static void TestCountFree()
{
	size_t num_of_blocks = 4;
	size_t block_size = 16;
	size_t pool_size = FsaSuggestSize(num_of_blocks, block_size);
	size_t counters[5] = {0};
	void* not_important = NULL;
	fsa_t *fsa = NULL;
	size_t i = 0;
	int is_working = 1;
	size_t tester = 5;
	
	void* pool = malloc(pool_size);
	
	fsa = FsaInit(pool, pool_size, block_size);
	
	for(; i < (num_of_blocks + 1); ++i)
	{
		counters[i] = FsaCountFree(fsa);
		not_important = FsaAlloc(fsa);
		(void) not_important;
	}
	
	for(i = 0; i < 5; ++i)
	{
		--tester;
		if(tester != counters[i])
		{
			is_working = 0;
			break;
		}
	}
	
	if(1 == is_working)
	{
		printf("FsaCountFree working!                                V\n");
	}
	else
	{
		printf("FsaCountFree NOT working!                            X\n");
	}
	
	free(pool);
}



