#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

#include "vsa.h"

static void TestAllFuncs();
static void TestInit();
static void TestAlloc();
static void TestFree();
static void TestLargestChunk();

int main()
{
    TestAllFuncs();
    return (0);
}

static void TestAllFuncs()
{
    printf("     ~START OF TEST FUNCTION~ \n");
    TestInit();
    TestAlloc();
    TestFree(); 
    TestLargestChunk();
    printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestInit()
{
    int pool_size = 100;
    int size_left = 0;
    vsa_t *vsa = NULL;
    
    void *pool = malloc(pool_size);
    vsa = VsaInit(pool, pool_size);
    size_left = VsaLargestChunkAvaliable(vsa);
    
    if(68 == size_left)
    {
        printf("VsaInit working!                                     V\n");
    }
    else
    {
        printf("VsaInit NOT working!                                 X\n");
    }
    
    free(pool);
}

static void TestAlloc()
{
    size_t pool_size = 300;
    size_t addresses[10] = {0};
    int i = 0;
    int is_working = 1;
    vsa_t *vsa = NULL;
    
    void *pool = malloc(pool_size);
    vsa = VsaInit(pool, pool_size);
    
    for(i = 0; i < 10; ++i)
    {
        addresses[i] = (size_t)VsaAlloc(vsa, 30);
    }
    
    for(i = 0; i < 9; ++i)
    {
        if(i < 5 && 0 == addresses[i] && (addresses[i+1] - addresses[i]) != 48)
        {
            is_working = 0;
            break;
        }
        
        if(i >= 5 && 0 != addresses[i])
        {
            is_working = 0;
            break;
        }
    }
    
    if(28 != VsaLargestChunkAvaliable(vsa))
    {
        is_working = 0;
    }
    
    if(1 == is_working)
    {
        printf("VsaAlloc working!                                    V\n");
    }
    else
    {
        printf("VsaAlloc NOT working!                                X\n");
    }
    
    free(pool);
}

static void TestFree()
{
	size_t pool_size = 300;
    size_t addresses[10] = {0};
    int i = 0;
    int is_working = 1;
    vsa_t *vsa = NULL;
    void *free1 = NULL;
    void *free2 = NULL;
    
    void *pool = malloc(pool_size);
    vsa = VsaInit(pool, pool_size);
    
    for(i = 0; i < 10; ++i)
    {
        addresses[i] = (size_t)VsaAlloc(vsa, 30);
    }
    
    for(i = 0; i < 9; ++i)
    {
        if(i < 5 && 0 == addresses[i] && (addresses[i+1] - addresses[i]) != 48)
        {
            is_working = 0;
            break;
        }
        
        if(i >= 5 && 0 != addresses[i])
        {
            is_working = 0;
            break;
        }
    }

    free1 = (void *)addresses[3];
    free2 = (void *)addresses[2];
    VsaFree(free1);
    VsaFree(free2);
    
    if(80 != VsaLargestChunkAvaliable(vsa))
    {
        is_working = 0;
    }
    
    if(1 == is_working)
    {
        printf("VsaFree working!                                     V\n");
    }
    else
    {
        printf("VsaFree NOT working!                                 X\n");
    }
    
    free(pool);
}

static void TestLargestChunk()
{
	size_t pool_size = 300;
    size_t addresses[10] = {0};
    int i = 0;
    int is_working = 1;
    vsa_t *vsa = NULL;
    void *free1 = NULL, *free2 = NULL;
    
    void *pool = malloc(pool_size);
    vsa = VsaInit(pool, pool_size);
    
    for(i = 0; i < 10; ++i)
    {
        addresses[i] = (size_t)VsaAlloc(vsa, 30);
    }
    
    for(i = 0; i < 9; ++i)
    {
        if(i < 5 && 0 == addresses[i] && (addresses[i+1] - addresses[i]) != 48)
        {
            is_working = 0;
            break;
        }
        
        if(i >= 5 && 0 != addresses[i])
        {
            is_working = 0;
            break;
        }
    }

    free1 = (void *)addresses[3];
    free2 = (void *)addresses[2];
    VsaFree(free1);

    if(32 != VsaLargestChunkAvaliable(vsa))
    {
        is_working = 0;
    }
    
    VsaFree(free2);
    
    if(80 != VsaLargestChunkAvaliable(vsa))
    {
        is_working = 0;
    }
    
    VsaAlloc(vsa, 29);
    
    if(32 != VsaLargestChunkAvaliable(vsa))
    {
        is_working = 0;
    }
    
    if(1 == is_working)
    {
        printf("VsaLargestChunkAvaliable working!                    V\n");
    }
    else
    {
        printf("VsaLargestChunkAvaliable NOT working!                X\n");
    }
    
    free(pool);
}





