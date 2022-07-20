/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#define FALSE 0
#define TRUE 1
#define CYCLIC 0
#define SUCCESS 0
#define FAIL 1

#include "scheduler_heap.h"
#include "pq_heap.h"

/*============================== DECLARATIONS ===============================*/

static int SortByTime(const void*, const void*);
static int CompareByUID(const void*, const void*);
static int CheckRunStatus(scheduler_t*);
static void SleepTillReady(int);

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct scheduler
{
	pq_heap_t *queue;
	int is_running;
};

 /* Approved by Tzach */
scheduler_t* HSchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t*) malloc(sizeof(scheduler_t));
	
	if(NULL != scheduler)
	{
		scheduler->is_running = FALSE;
		scheduler->queue = PQHeapCreate(SortByTime);
		
		if(NULL == scheduler->queue)
		{
			free(scheduler);
			scheduler = NULL;
		}
	}
	return (scheduler);
}

void HSchedulerDestroy(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    
    HSchedulerClear(scheduler);
    PQHeapDestroy(scheduler->queue);
    scheduler->queue = NULL;
    free(scheduler);
}

UID_t HSchedulerAddTask(scheduler_t *scheduler, action_func *func, void* param, size_t interval)
{
	task_t *new_task = NULL;
	int added_to_queue = -1;
	UID_t uid_to_return = badUID;
	
	assert(NULL != scheduler);
	assert(NULL != func);
	
	new_task = TaskCreate(func, interval, param);
	
	if(NULL != new_task)
	{
		added_to_queue = PQHeapEnqueue(scheduler->queue, (void*)new_task);
		
		if(success != added_to_queue)
		{
			TaskDestroy(new_task);
		}
		else
		{
			uid_to_return = TaskGetUID(new_task);
		}
	}
	
	return (uid_to_return);
}

int HSchedulerRemoveTask(scheduler_t *scheduler, UID_t uid)
{
	void *removed = NULL;
	
	assert(NULL != scheduler);
	
	removed = PQHeapErase(scheduler->queue, CompareByUID, (void*)&uid);
	if(NULL != removed)
	{
		TaskDestroy(removed);
	}
	return (NULL != removed);
}

void HSchedulerClear(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    
    while(!HSchedulerIsEmpty(scheduler))
    {
        TaskDestroy(PQHeapDequeue(scheduler->queue));
    }
}

int HSchedulerRun(scheduler_t *scheduler)
{	
	assert(NULL != scheduler);
	
	scheduler->is_running = TRUE;
	
	while((TRUE == scheduler->is_running) && (!HSchedulerIsEmpty(scheduler)))
	{
		task_t *curr_task = (task_t*)PQHeapDequeue(scheduler->queue);
		int is_cyclic = -1;
		
		SleepTillReady(TaskGetNextRunTime(curr_task) - time(0));
		
		is_cyclic = TaskRun(curr_task);
		
		if(CYCLIC == is_cyclic)
		{
			TaskUpdateNextRunTime(curr_task);
			
			if(FAIL == PQHeapEnqueue(scheduler->queue, (void*)curr_task))
			{
				TaskDestroy(curr_task);
				break;
			}
		}
		else
		{
			TaskDestroy(curr_task);
		}
	}
	
	return (CheckRunStatus(scheduler));
}

void HSchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->is_running = FALSE;
}

size_t HSchedulerSize(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQHeapSize(scheduler->queue));
}

int HSchedulerIsEmpty(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQHeapIsEmpty(scheduler->queue));
}


static int CheckRunStatus(scheduler_t *scheduler)
{
	int status = fail;
	
	if(FALSE == scheduler->is_running)
    {
        status = stop_run;
    }
    
    if(HSchedulerIsEmpty(scheduler))
    {
    	status = success;
	}
	
	return (status);
}

static void SleepTillReady(int time_delta)
{
	while(0 < time_delta)
	{
		sleep(1);
		--time_delta;
	}
}

static int SortByTime(const void *task, const void *task2)
{
	return (TaskGetNextRunTime((task_t*)task2) - TaskGetNextRunTime((task_t*)task));
}

static int CompareByUID(const void* task,const void* param)
{
	return (TaskCompare((task_t*)task, *(UID_t*)param));
}







