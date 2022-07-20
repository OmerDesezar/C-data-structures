#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

#include "../include/queue.h"

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
    queue_ptr_t queue_to_append = QCreate();
    queue_ptr_t queue = QCreate();
	
	if(NULL != queue)
    {
    	printf("QCreate working!                                     V\n");
	}
	else
	{
		printf("QCreate NOT working!                                 X\n");
	}
	
	if(QIsEmpty(queue))
    {
    	printf("QIsEmpty working!                                    V\n");
	}
	else
	{
		printf("QIsEmpty NOT working!                                X\n");
	}
    
    for(i = 0;i < 100;++i)
    {
        arr[i] = i;
        QEnQueue(queue, (void *)&arr[i]);
    }

    if(100 == QGetSize(queue))
    {
    	printf("QGetSize working!                                    V\n");
	}
	else
	{
		printf("QGetSize NOT working!                                X\n");
	}
    
    if(0 == *(int*)QPeek(queue))
    {
    	printf("QPeek & QEnQueue working!                            V\n");
	}
	else
	{
		printf("QPeek & QEnQueue NOT working!                        X\n");
	}
    
    QDeQueue(queue);
    
    if((99 == QGetSize(queue)) && (1 == *(int*)QPeek(queue)))
    {
    	printf("QDeQueue working!                                    V\n");
	}
	else
	{
		printf("QDeQueue NOT working!                                X\n");
	}
	
	for(i = 0;i < 15;++i)
    {
        arr2[i] = i;
        QEnQueue(queue_to_append, (void *)&arr2[i]);
    }
    
	QAppend(queue, queue_to_append);
	
	if((114 == QGetSize(queue)) && (0 == QGetSize(queue_to_append)))
    {
    	printf("QAppend working!                                     V\n");
	}
	else
	{
		printf("QAppend NOT working!                                 X\n");
	}
	
    QDestroy(queue);
    QDestroy(queue_to_append);
    
    printf(" ~ END OF TEST FUNCTION ~\n");
}




