/*=========================== LIBRARIES & MACROS ============================*/
#include <pthread.h>
#include "UID.h"

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* Approved by Tzach */
const UID_t badUID = {(clock_t)0,(pid_t)0,(size_t)0};

static atomic_size_t counter = 0;

UID_t UIDCreate(void)
{
	UID_t new_UID = badUID;
	pthread_mutex_lock(&lock);
	new_UID.counter = counter;
	atomic_fetch_add(&counter, 1);
	new_UID.time = clock();
	new_UID.pid = getpid();
	pthread_mutex_unlock(&lock);
	return (new_UID);
}

int UIDIsSame(UID_t UID1, UID_t UID2)
{
	return((UID1.counter == UID2.counter) && 
	(UID1.time == UID2.time) && 
	(UID1.pid == UID2.pid));
}
