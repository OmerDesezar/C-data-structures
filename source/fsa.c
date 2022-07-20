/*=========================== LIBRARIES & MACROS ============================*/

#include <assert.h> /* assert */
#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))
#define STRUCT_OFFSET (ALIGN_UP_TO_WS(sizeof(fsa_t)))
#define ALIGN_UP_TO_WS(x) ((x + (WORD_SIZE -1)) & (~(WORD_SIZE - 1)))
#define LAST_BLOCK ((size_t)0)

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct fsa
{
	size_t next_avaliable;
	size_t block_size;
};

/* Approved by Asaf */
fsa_t *FsaInit(void *pool_start, size_t pool_size, size_t block_size)
{
    fsa_t *fsa = NULL;
    char *byte_writer = NULL;
    char *pool_end = (char*)pool_start + pool_size;

	assert(NULL != pool_start);
	assert(0 != block_size);
	assert(pool_size > block_size);
    
    block_size = ALIGN_UP_TO_WS(block_size);
    byte_writer = (char*)pool_start + STRUCT_OFFSET;
    
    fsa = (fsa_t*)pool_start;
    fsa->block_size = block_size;
    fsa->next_avaliable = STRUCT_OFFSET;

    while ((byte_writer + block_size) < pool_end)
    {
        *(size_t*)byte_writer = (byte_writer - (char*)pool_start) + block_size;
        byte_writer += block_size;
    }
    
    *(size_t*)byte_writer = LAST_BLOCK;
    
    return (fsa);
}

void* FsaAlloc(fsa_t *fsa)
{
	void *to_return = NULL;
	
	assert(NULL != fsa);
	
	if(LAST_BLOCK != fsa->next_avaliable)
	{
		to_return = (char*)fsa + fsa->next_avaliable;
		fsa->next_avaliable = *((size_t*)to_return);
	}
	
	return(to_return);
}

void FsaFree(fsa_t *fsa, void *block_ptr)
{
	assert(NULL != fsa);
	assert(NULL != block_ptr);
	
	*(size_t*)block_ptr = fsa->next_avaliable;
	fsa->next_avaliable = (size_t)block_ptr - (size_t)fsa;
}

size_t FsaCountFree(const fsa_t *fsa)
{
	size_t counter = 0;
	size_t runner = 0;

	assert(NULL != fsa);
	
	runner = fsa->next_avaliable;
	
	while(LAST_BLOCK != runner)
	{
		++counter;
		runner = *(size_t*)((size_t)fsa + runner);
	}
	
	return (counter);
}

size_t FsaSuggestSize(size_t num_of_blocks, size_t block_size)
{
	return ((ALIGN_UP_TO_WS(block_size) * num_of_blocks) + STRUCT_OFFSET);
}


