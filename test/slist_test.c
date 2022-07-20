#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

#include "../include/slist.h"

int AddToNum(void* ptr, void* param);
int IntMatch(const void *data, const void *param);
void TestAllFuncs();

int main()
{
	TestAllFuncs();
	return (0);
}

void TestAllFuncs()
{
    int arr[100];
    int arr2[15];
    int i = 0;
    int fifty = 50;
    int num = 10;
    int to_find = 45;
    slist_iter_t iter = NULL;
    slist_iter_t iter_end = NULL;
    slist_iter_t found_iter = NULL;
    slist_ptr_t list = NULL;
    slist_ptr_t list_to_append = NULL;

	list = SListCreate();
	iter = SListBegin(list);
	
	if(NULL != list)
    {
    	printf("SListCreate working!                                 V\n");
	}
	else
	{
		printf("SListCreate NOT working!                             X\n");
	}
    
    if(0 == SListCount(list))
    {
    	printf("SListCount working!                                  V\n");
	}
	else
	{
		printf("SListCount NOT working!                              X\n");
	}
    
    for(i = 0;i < 100;++i)
    {
        arr[i] = i;
        iter = SListInsertBefore(iter, (void *)&arr[i]);
    }
    
    if(100 == SListCount(list))
    {
    	printf("SListInsertBefore working!                           V\n");
	}
	else
	{
		printf("SListInsertBefore NOT working!                       X\n");
	}
    
    iter = SListBegin(list);
    iter_end = SListEnd(list);
    
    if(99 == *(int *)SListGetData(iter))
    {
    	printf("SListBegin & SListGetData working!                   V\n");
	}
	else
	{
		printf("SListBegin & SListGetData NOT working!               X\n");
	}
	
	if(list == SListGetData(iter_end))
    {
    	printf("SListEnd working!                                    V\n");
	}
	else
	{
		printf("SListEnd NOT working!                                X\n");
	}
	
	SListRemove(iter);
	
    if(98 == *(int *)SListGetData(iter))
    {
    	printf("SListRemove working!                                 V\n");
	}
	else
	{
		printf("SListRemove NOT working!                             X\n");
	}
    
	SListSetData(iter, (void *)&fifty);
	
	if(50 == *(int *)SListGetData(iter))
    {
    	printf("SListSetData working!                                V\n");
	}
	else
	{
		printf("SListSetData NOT working!                            X\n");
	}
	
	iter = SListIterNext(iter);
	
	if(97 == *(int *)SListGetData(iter))
    {
    	printf("SListIterNext working!                               V\n");
	}
	else
	{
		printf("SListIterNext NOT working!                           X\n");
	}
	
	iter = SListBegin(list);
    iter_end = SListEnd(list);

	SListForEach(iter, iter_end, AddToNum, (void*)&num);
	
	if(60 == *(int *)SListGetData(iter))
    {
    	printf("SListForEach working!                                V\n");
	}
	else
	{
		printf("SListForEach NOT working!                            X\n");
	}
	
	found_iter = SListFind(iter, iter_end, IntMatch, (void*)&to_find);

	if(45 == *(int *)SListGetData(found_iter))
    {
    	printf("SListFind working!                                   V\n");
	}
	else
	{
		printf("SListFind NOT working!                               X\n");
	}
	
	list_to_append = SListCreate();
	iter = SListBegin(list_to_append);
	
	for(i = 0;i < 15;++i)
    {
        arr2[i] = i;
        iter = SListInsertBefore(iter, (void *)&arr2[i]);
    }
    
	SListAppend(list, list_to_append);
	
	if((114 == SListCount(list)) && (0 == SListCount(list_to_append)))
    {
    	printf("SListAppend working!                                 V\n");
	}
	else
	{
		printf("SListAppend NOT working!                             X\n");
	}
	
    SListDestroy(list);
    SListDestroy(list_to_append);
    
    printf(" ~ END OF TEST FUNCTION ~\n");
}


int AddToNum(void* ptr, void* param)
{
	*(int*)ptr += *(int*)param;
	return (0);
}

int IntMatch(const void *data, const void *param)
{
    return (*(int *)data == *(int *)param);
}



