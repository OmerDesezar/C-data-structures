#include <pthread.h> /* threads */
#include <stdio.h> /* printf */

#include "UID.h"

#define SIZE 100
#define THREAD_COUNT 10
#define RANGE (SIZE/THREAD_COUNT)

static void TestAllFuncs();
static void TestCreate();
static void TestIsSame();
static void TestThreadSafety();
static void *GenUIDs(void*);

static UID_t uids[SIZE];

int main()
{
	TestAllFuncs();
	return (0);
}

static void TestAllFuncs()
{
	printf("     ~START OF TEST FUNCTION~ \n");
	TestCreate();
	TestIsSame();
	TestThreadSafety();
	printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
	UID_t uid = UIDCreate();
	UID_t uid2 = UIDCreate();
	if(uid2.counter > uid.counter && uid.pid == uid2.pid)
	{
		printf("UIDCreate working!                                   V\n");
	}
	else
	{
		printf("UIDCreate NOT working!                               X\n");
	}

}

static void TestIsSame()
{
	UID_t uid = UIDCreate();
	UID_t uid2 = uid;
	
	if((UIDIsSame(uid, uid2)) && (!UIDIsSame(uid, badUID)))
	{
		printf("UIDIsSame working!                                   V\n");
	}
	else
	{
		printf("UIDIsSame NOT working!                               X\n");
	}
}

static void TestThreadSafety()
{
	int status = 1;
	pthread_t threads[THREAD_COUNT];
	size_t i = 0, j = 0;

	for (i = 0; i < THREAD_COUNT; ++i)
	{
		pthread_create(&threads[i], NULL, GenUIDs, (void *)i);
	}

	for (i = 0; i < THREAD_COUNT; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = i + 1; j < SIZE; j++)
		{

			if (UIDIsSame(uids[i], uids[j]) && i != j)
			{
				status = 0;
				break;
			}
		}
	}
	if(status)
	{
		printf("UIDCreate thread safe!                               V\n");
	}
	else
	{
		printf("UIDCreate NOT thread safe!                           X\n");
	}
}

static void *GenUIDs(void *index)
{
	int i = (size_t)index * RANGE + 1;
	int limit = i + RANGE;
	for (; i < limit; ++i)
	{
		uids[i] = UIDCreate();
	}
	return (NULL);
}





