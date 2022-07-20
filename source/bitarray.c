
/*##########################LIBRARIES & MACROS#################################*/

#include <limits.h> /* ULONG_MAX */
#include <assert.h> /* assert */

#include "bitarray.h"

#define ARR_LEN (sizeof(bitarray_t) * CHAR_BIT)

/*#############################DECLARATIONS####################################*/

static void InitCountLUT();
static void InitMirrorLUT();
static unsigned char MirrorChar(unsigned char);

static size_t COUNT_LUT[256] = {0};
static size_t MIRROR_LUT[256] = {0};

/*##########################FUNCTION DEFINITIONS###############################*/

/* Approved by Asaf */
bitarray_t BitArraySetAll(bitarray_t arr)
{
	(void)arr;

	return (bitarray_t)ULONG_MAX;
}

bitarray_t BitArrayResetAll(bitarray_t arr)
{
	(void)arr;

	return ((bitarray_t)0);
}

int BitArrayGetVal(bitarray_t arr, size_t index)
{
	assert(ARR_LEN >= index);
	return ((arr >> (index)) & (bitarray_t)1);
}

bitarray_t BitArraySetBit(bitarray_t arr, size_t index, int value)
{
	bitarray_t temp = 1;
	assert(1 == value || 0 == value);
	assert(ARR_LEN > index);
	temp <<= (index);

	if (0 == value)
	{
		return (arr & (~temp));
	}

	return (arr | temp);
}

bitarray_t BitArraySetOn(bitarray_t arr, size_t index)
{
	assert(ARR_LEN > index);

	return (BitArraySetBit(arr, index, 1));
}

bitarray_t BitArraySetOff(bitarray_t arr, size_t index)
{
	assert(ARR_LEN > index);

	return (BitArraySetBit(arr, index, 0));
}

bitarray_t BitArrayFlip(bitarray_t arr, size_t index)
{
	bitarray_t temp = 1;
	assert(ARR_LEN > index);
	temp <<= (index);

	return (arr ^ temp);
}

bitarray_t BitArrayRotR(bitarray_t arr, size_t num_of_rotations)
{
	num_of_rotations %= ARR_LEN;

	return ((arr >> num_of_rotations) | (arr << (ARR_LEN - num_of_rotations)));
}

bitarray_t BitArrayRotL(bitarray_t arr, size_t num_of_rotations)
{
	num_of_rotations %= ARR_LEN;

	return ((arr << num_of_rotations) | (arr >> (ARR_LEN - num_of_rotations)));
}

bitarray_t BitArrayMirror(bitarray_t arr)
{
	bitarray_t new_arr = 0;
	bitarray_t runner = 1;

	for (; 0 != runner; runner <<= 1)
	{
		new_arr <<= 1;
		new_arr = new_arr | (arr & (bitarray_t)1);
		arr >>= 1;
	}

	return (new_arr);
}

bitarray_t BitArrayMirrorNoLoop(bitarray_t arr)
{
	arr = ((arr) >> 32) | ((arr) << 32);
	arr = ((arr & 0xFFFF0000FFFF0000) >> 16) | ((arr & 0x0000FFFF0000FFFF) << 16);
	arr = ((arr & 0xFF00FF00FF00FF00) >> 8) | ((arr & 0x00FF00FF00FF00FF) << 8);
	arr = ((arr & 0xF0F0F0F0F0F0F0F0) >> 4) | ((arr & 0x0F0F0F0F0F0F0F0F) << 4);
	arr = ((arr & 0xCCCCCCCCCCCCCCCC) >> 2) | ((arr & 0x3333333333333333) << 2);
	arr = ((arr & 0xAAAAAAAAAAAAAAAA) >> 1) | ((arr & 0x5555555555555555) << 1);

	return (arr);
}

bitarray_t BitArrayMirrorLUT(bitarray_t arr)
{
	bitarray_t mirrored_arr = 0;
	int i = 0;

	InitMirrorLUT();

	for (; i < 8; ++i)
	{
		mirrored_arr += (MIRROR_LUT[(arr >> (i * 8)) & 0xFF]) << (56 - (i * 8));
	}

	return (mirrored_arr);
}

size_t BitArrayCountOn(bitarray_t arr)
{
	size_t counter = 0;

	while (arr > 0)
	{
		arr = arr & (arr - 1);
		++counter;
	}

	return (counter);
}

size_t BitArrayCountOnNoLoop(bitarray_t arr)
{
	bitarray_t left_temp = 0;
	bitarray_t right_temp = 0;
	bitarray_t combined = 0;

	left_temp = arr & 0x5555555555555555;
	right_temp = (arr >> 1) & 0x5555555555555555;
	combined = left_temp + right_temp;
	left_temp = combined & 0x3333333333333333;
	right_temp = (combined >> 2) & 0x3333333333333333;
	combined = left_temp + right_temp;
	left_temp = combined & 0x0F0F0F0F0F0F0F0F;
	right_temp = (combined >> 4) & 0x0F0F0F0F0F0F0F0F;
	combined = left_temp + right_temp;
	left_temp = combined & 0x00FF00FF00FF00FF;
	right_temp = (combined >> 8) & 0x00FF00FF00FF00FF;
	combined = left_temp + right_temp;
	left_temp = combined & 0x0000FFFF0000FFFF;
	right_temp = (combined >> 16) & 0x0000FFFF0000FFFF;
	combined = left_temp + right_temp;
	left_temp = combined & 0x00000000FFFFFFFF;
	right_temp = (combined >> 32) & 0x00000000FFFFFFFF;
	combined = left_temp + right_temp;

	return ((size_t)combined);
}

size_t BitArrayCountOnLUT(bitarray_t arr)
{
	size_t counter = 0;
	int i = 0;

	InitCountLUT();

	for (; i < 8; ++i)
	{
		counter += COUNT_LUT[(arr >> (i * 8)) & 0xFF];
	}

	return (counter);
}

size_t BitArrayCountOff(bitarray_t arr)
{
	return (ARR_LEN - BitArrayCountOn(arr));
}

char *BitArrayToString(bitarray_t arr, char *to_write_into)
{
	char *to_write_runner = to_write_into;
	size_t i = 0;

	for (; i < ARR_LEN; ++i)
	{
		*to_write_runner = ('0' + BitArrayGetVal(arr, ARR_LEN - i));
		++to_write_runner;
	}

	*to_write_runner = '\0';

	return (to_write_into);
}

static void InitCountLUT()
{
	size_t i = 0;

	if (1 == COUNT_LUT[1])
	{
		return;
	}

	for (; i < 256; ++i)
	{
		COUNT_LUT[i] = BitArrayCountOnNoLoop((bitarray_t)i);
	}
}

static void InitMirrorLUT()
{
	size_t i = 0;

	if (1 < MIRROR_LUT[1])
	{
		return;
	}

	for (; i < 256; ++i)
	{
		MIRROR_LUT[i] = MirrorChar((unsigned char)i);
	}
}

static unsigned char MirrorChar(unsigned char ch)
{
	ch = ((ch) >> 4) | ((ch) << 4);
	ch = ((ch & 0xCC) >> 2) | ((ch & 0x33) << 2);
	ch = ((ch & 0xAA) >> 1) | ((ch & 0x55) << 1);

	return (ch);
}

/* How did you get here? */