#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;


fsa_t* FsaInit(void* pool_start, const size_t pool_size, const size_t block_size);

void* FsaAlloc(fsa_t *fsa);

void FsaFree(fsa_t *fsa, void *block_ptr);

size_t FsaCountFree(const fsa_t *fsa);

size_t FsaSuggestSize(const size_t num_of_blocks, const size_t block_size);

#endif /* __FSA_H__ */

