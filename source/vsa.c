/*=========================== LIBRARIES & MACROS ============================*/
#include <assert.h> /* assert */

#include "vsa.h"

#define WORD_SIZE (sizeof(size_t))
#define ALIGN_UP_TO_WS(x) ((x + (WORD_SIZE -1)) & (~(WORD_SIZE - 1)))
#define STRUCT_SIZE (ALIGN_UP_TO_WS(sizeof(vsa_t)))
#define ABS(x) ((x < 0)?(-1 * x):(x))
#define MAX(A,B) ((A > B)?(A):(B))
#define VALIDATOR ((long) 0xDEADBEEF)
#define UNVALIDATOR ((long) 0xBAAAAAAD)
#define EMPTY 0

/*============================== DECLARATIONS ===============================*/

__inline__ static void SetValidator(vsa_t*, long);
static void Defragment(vsa_t*);
static void AddBlockIfPossible(vsa_t*, size_t);
static vsa_t *FindSuitableBlock(vsa_t*, size_t);

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct block_header
{
	long block_size;
	#ifndef NDEBUG
	long validator;
	#endif
};

typedef struct block_header block_t;

vsa_t *VsaInit(void *pool_start, size_t pool_size)
{
	vsa_t *vsa = NULL;
	block_t *vsa_end = NULL;
	
	assert(NULL != pool_start);
	assert(0 != pool_size);
	
	vsa = pool_start;
	vsa_end = (block_t*)((char*)vsa + pool_size - STRUCT_SIZE);
	
	vsa->block_size = pool_size - (2 * STRUCT_SIZE);
	SetValidator(vsa, VALIDATOR);
	
	vsa_end->block_size = EMPTY;
	SetValidator(vsa_end, VALIDATOR);
	
	return (vsa);
}

void *VsaAlloc(vsa_t *vsa, size_t block_size)
{
	void *to_return = NULL;
	vsa_t *vsa_start = vsa;
	
	assert(NULL != vsa);
	assert(0 != block_size);
	
	block_size = ALIGN_UP_TO_WS(block_size);
	vsa = FindSuitableBlock(vsa_start, block_size);
	
	if(EMPTY == vsa->block_size)
	{
		Defragment(vsa_start);
		vsa = FindSuitableBlock(vsa_start, block_size);
	}
	
	if(EMPTY != vsa->block_size)
	{
		AddBlockIfPossible(vsa, block_size);
		vsa->block_size = -(vsa->block_size);
		to_return = (char*)vsa + STRUCT_SIZE;
	}
	
	return (to_return);
}

void VsaFree(void *block_ptr)
{
	block_t *to_free = NULL;
	
	assert(NULL != block_ptr);
	
	to_free = (block_t*)((char*)block_ptr - STRUCT_SIZE);
	assert(VALIDATOR == to_free->validator);
	to_free->block_size = ABS(to_free->block_size);
}

size_t VsaLargestChunkAvaliable(vsa_t *vsa)
{
	size_t largest = 0;
	long curr_block_size = 0;
	
	assert(NULL != vsa);

	Defragment(vsa);
	
	do
	{
		curr_block_size = vsa->block_size;
		largest = MAX((long)largest, curr_block_size);
		vsa = (vsa_t*)((char*)vsa + STRUCT_SIZE + ABS(curr_block_size));
	} while (EMPTY != curr_block_size);
	
	return (largest);
}

__inline__ static void SetValidator(vsa_t *vsa, long validator)
{
	#ifndef NDEBUG
	vsa->validator = validator;
	#endif
	(void)vsa;
	(void)validator;
}

static void Defragment(vsa_t *vsa)
{
	vsa_t *vsa_next = NULL;
	
	do
	{
		vsa_next = (vsa_t*)((char*)vsa + STRUCT_SIZE + ABS(vsa->block_size));
		
		if(vsa->block_size > 0 && vsa_next->block_size > 0)
		{
			vsa->block_size += vsa_next->block_size + STRUCT_SIZE;
			SetValidator(vsa_next, UNVALIDATOR);
			continue;
		}
		
		vsa = vsa_next;
	} while(EMPTY != vsa_next->block_size);
}

static void AddBlockIfPossible(vsa_t *vsa, size_t block_size)
{
	vsa_t *new_block = NULL;
	long curr_block_size = vsa->block_size;
	
	if((long)(block_size + STRUCT_SIZE) < curr_block_size)
		{
			new_block = (vsa_t*)((char*)vsa + STRUCT_SIZE + block_size);
			new_block->block_size = curr_block_size - block_size - STRUCT_SIZE;
			SetValidator(new_block, VALIDATOR);
			vsa->block_size = block_size;
		}
}

static vsa_t *FindSuitableBlock(vsa_t *vsa, size_t block_size)
{
	long curr_block_size = vsa->block_size;
	
	while(EMPTY != curr_block_size && (long)block_size > curr_block_size)
	{
		vsa = (vsa_t*)((char*)vsa + STRUCT_SIZE + ABS(curr_block_size));
		curr_block_size = vsa->block_size;
	}
	
	return (vsa);
}


