/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "scheduler.h"

#define FALSE 0
#define TRUE 1
#define CYCLIC 0


/*============================== DECLARATIONS ===============================*/

static int SortByTime(const void*, const void*);
static int CompareByUID(const void*, const void*);
static int CheckRunStatus(scheduler_t*);
static void SleepTillReady(int);

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct scheduler
{
	priority_q_t *queue;
	int is_running;
};

 /* Approved by Tzach */
scheduler_t* SchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t*) malloc(sizeof(scheduler_t));
	
	if(NULL != scheduler)
	{
		scheduler->is_running = FALSE;
		scheduler->queue = PriorityQCreate(SortByTime);
		
		if(NULL == scheduler->queue)
		{
			free(scheduler);
			scheduler = NULL;
		}
	}
	
	return (scheduler);
}

void SchedulerDestroy(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    
    SchedulerClear(scheduler);
    PriorityQDestroy(scheduler->queue);
    scheduler->queue = NULL;
    free(scheduler);
}

UID_t SchedulerAddTask(scheduler_t *scheduler, action_func *func, void* param, size_t interval_in_seconds)
{
	task_t *new_task = NULL;
	int added_to_queue = -1;
	UID_t uid_to_return = badUID;
	
	assert(NULL != scheduler);
	assert(NULL != func);
	
	new_task = TaskCreate(func, interval_in_seconds, param);
	
	if(NULL != new_task)
	{
		added_to_queue = PriorityQEnqueue(scheduler->queue, (void*)new_task);
		
		if(0 == added_to_queue)
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

int SchedulerRemoveTask(scheduler_t *scheduler, UID_t uid)
{
	task_t *removed;
	int return_status = -1;
	
	assert(NULL != scheduler);
	
	removed = (task_t*)PriorityQErase(scheduler->queue, CompareByUID, (void*)&uid);
	return_status = (NULL == removed);
	TaskDestroy(removed);
	
	return(return_status);
}

void SchedulerClear(scheduler_t *scheduler)
{
    assert(NULL != scheduler);
    
    while(!SchedulerIsEmpty(scheduler))
    {
        TaskDestroy((task_t *)PriorityQDequeue(scheduler->queue));
    }
}

int SchedulerRun(scheduler_t *scheduler)
{	
	assert(NULL != scheduler);
	
	scheduler->is_running = TRUE;
	
	while((TRUE == scheduler->is_running) && (!SchedulerIsEmpty(scheduler)))
	{
		task_t *curr_task = (task_t*)PriorityQDequeue(scheduler->queue);
		int is_cyclic = -1;
		
		SleepTillReady(TaskGetNextRunTime(curr_task) - time(0));
		
		is_cyclic = TaskRun(curr_task);
		
		if(CYCLIC == is_cyclic)
		{
			TaskUpdateNextRunTime(curr_task);
			
			if(0 == PriorityQEnqueue(scheduler->queue, (void*)curr_task))
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

void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->is_running = FALSE;
}

size_t SchedulerSize(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PriorityQSize(scheduler->queue));
}

int SchedulerIsEmpty(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PriorityQIsEmpty(scheduler->queue));
}


static int CheckRunStatus(scheduler_t *scheduler)
{
	int status = fail;
	
	if(FALSE == scheduler->is_running)
    {
        status = stop_run;
    }
    
    if(SchedulerIsEmpty(scheduler))
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







