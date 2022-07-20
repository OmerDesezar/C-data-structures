/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "../include/circbuff.h"

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
#define DATA_ARRAY_START (4 * sizeof(size_t))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define READ_INDEX 2
#define WRITE_INDEX 3
#define INCREASE 1
#define DECREASE -1

/*============================= DECLARATIONS ================================*/

static void ChangeElementCount(circbuff_ptr_t, int);
static size_t GetIndex(const circbuff_ptr_t, int);
static void IncreaseIndex(circbuff_ptr_t, int);

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

/* 
 * buff[0] = element_count
 * buff[1] = capacity
 * buff[2] = read_index
 * buff[3] = write_index
 */
typedef struct circbuff
{
	size_t buff[4];
}cb_t;

 /* Approved by Tzach */
 
circbuff_ptr_t CircBuffCreate(size_t capacity)
{
	circbuff_ptr_t buffer = malloc(sizeof(cb_t) + capacity);
	
	buffer->buff[0] = 0;
	buffer->buff[1] = capacity;
	buffer->buff[2] = DATA_ARRAY_START;
	buffer->buff[3] = DATA_ARRAY_START;
	
	return (buffer);
}

void CircBuffDestroy(circbuff_ptr_t buffer)
{
	assert(NULL != buffer);
	free(buffer);
}

ssize_t CircBuffWrite(circbuff_ptr_t buffer, const void *to_read_from, size_t num_of_bytes)
{
	char* read_char_runner = (char*) to_read_from;
	char* write_char_runner = (char*) buffer->buff;
	ssize_t counter = num_of_bytes;
	
	assert(NULL != buffer);
	assert(NULL != to_read_from);
	
	while(0 < num_of_bytes--)
	{
		write_char_runner[GetIndex(buffer, WRITE_INDEX)] = *read_char_runner++;
		IncreaseIndex(buffer, WRITE_INDEX);
		ChangeElementCount(buffer, INCREASE);
	}
	
	return (counter);
}

ssize_t CircBuffRead(circbuff_ptr_t buffer, void *to_write_to, size_t num_of_bytes)
{
	char* write_char_runner = (char*) to_write_to;
	char* read_char_runner = (char*) buffer->buff;
	ssize_t counter = MIN(num_of_bytes, CircBuffSize(buffer));
	
	assert(NULL != buffer);
	assert(NULL != to_write_to);

	while((0 < num_of_bytes--) && !(CircBuffIsEmpty(buffer)))
	{
		*write_char_runner++ = read_char_runner[GetIndex(buffer, READ_INDEX)];
		IncreaseIndex(buffer, READ_INDEX);
		ChangeElementCount(buffer, DECREASE);
	}
	
	return (counter);
}

int CircBuffIsEmpty(const circbuff_ptr_t buffer)
{
	assert(NULL != buffer);
	return (0 == buffer->buff[0]);
}

size_t CircBuffSize(const circbuff_ptr_t buffer)
{
	assert(NULL != buffer);
	return (buffer->buff[0]);
}

size_t CircBuffFreeSpace(const circbuff_ptr_t buffer)
{
	assert(NULL != buffer);
	return (buffer->buff[1] - buffer->buff[0]);
}


static size_t GetIndex(const circbuff_ptr_t buffer, int num)
{
	return (buffer->buff[num]);
}

static void IncreaseIndex(circbuff_ptr_t buffer, int num)
{
	++buffer->buff[num];
	
	if(buffer->buff[num] > (buffer->buff[1] + DATA_ARRAY_START - 1))
		{
			buffer->buff[num] = DATA_ARRAY_START;
		}
}

static void ChangeElementCount(circbuff_ptr_t buffer, int num)
{
	buffer->buff[0] += num;
	
	if(buffer->buff[0] > buffer->buff[1])
		{
			--buffer->buff[0];
			buffer->buff[READ_INDEX] = buffer->buff[WRITE_INDEX];
		}
}








