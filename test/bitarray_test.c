#include <stdio.h>	/* printf */
#include <limits.h> /* ULONG_MAX */

#include "bitarray.h"

static void TestAllFuncs();

int main()
{
	TestAllFuncs();
	return (0);
}

static void TestSetAll()
{
	bitarray_t test = 0;
	test = BitArraySetAll(test);
	if (test == ULONG_MAX)
	{
		printf("BitArraySetAll working!               V\n");
	}
	else
	{
		printf("BitArraySetAll NOT working!           X\n");
	}
}

static void TestResetAll()
{
	bitarray_t test = 9988776655;
	test = BitArrayResetAll(test);
	if (test == 0)
	{
		printf("BitArrayResetAll working!             V\n");
	}
	else
	{
		printf("BitArrayResetAll NOT working!         X\n");
	}
}

static void TestGetVal()
{
	bitarray_t test = 16;
	int num = BitArrayGetVal(test, 4);
	if (num == 1)
	{
		printf("BitArrayGetVal working!               V\n");
	}
	else
	{
		printf("BitArrayGetVal NOT working!           X\n");
	}
}

static void TestSetBit()
{
	bitarray_t test = 0;
	test = BitArraySetBit(test, 5, 1);
	if (test == 32)
	{
		printf("BitArraySetBit working!               V\n");
	}
	else
	{
		printf("BitArraySetBit NOT working!           X\n");
	}
}

static void TestSetOn()
{
	bitarray_t test = 0;
	test = BitArraySetOn(test, 5);
	if (test == 32)
	{
		printf("BitArraySetOn working!                V\n");
	}
	else
	{
		printf("BitArraySetOn NOT working!            X\n");
	}
}

static void TestSetOff()
{
	bitarray_t test = 16;
	test = BitArraySetOff(test, 4);
	if (test == 0)
	{
		printf("BitArraySetOff working!               V\n");
	}
	else
	{
		printf("BitArraySetOff NOT working!           X\n");
	}
}

static void TestFlip()
{
	bitarray_t test = 0;
	test = BitArrayFlip(test, 5);
	if (test == 32)
	{
		printf("BitArrayFlip working!                 V\n");
	}
	else
	{
		printf("BitArrayFlip NOT working!             X\n");
	}
}

static void TestRotR()
{
	bitarray_t test = 1;
	test = BitArrayRotR(test, 1);
	if (test == 0x8000000000000000)
	{
		printf("BitArrayRolR working!                 V\n");
	}
	else
	{
		printf("BitArrayRolR NOT working!             X\n");
	}
}

static void TestRotL()
{
	bitarray_t test = 1;
	test = BitArrayRotL(test, 5);
	if (test == 32)
	{
		printf("BitArrayRolL working!                 V\n");
	}
	else
	{
		printf("BitArrayRolL NOT working!             X\n");
	}
}

static void TestMirror()
{
	bitarray_t test = 1;
	test = BitArrayMirror(test);
	if (test == 0x8000000000000000)
	{
		printf("BitArrayMirror working!               V\n");
	}
	else
	{
		printf("BitArrayMirror NOT working!           X\n");
	}
}

static void TestMirrorNoLoop()
{
	bitarray_t test = 1;
	test = BitArrayMirrorNoLoop(test);
	if (test == 0x8000000000000000)
	{
		printf("BitArrayMirrorNoLoop working!         V\n");
	}
	else
	{
		printf("BitArrayMirrorNoLoop NOT working!     X\n");
	}
}

static void TestMirrorLUT()
{
	bitarray_t test = 1;
	test = BitArrayMirrorLUT(test);
	if (test == 0x8000000000000000)
	{
		printf("BitArrayMirrorLUT working!            V\n");
	}
	else
	{
		printf("BitArrayMirrorLUT NOT working!        X\n");
	}
}

static void TestCountOn()
{
	bitarray_t test = 150;
	size_t num = BitArrayCountOn(test);
	if (num == 4)
	{
		printf("BitArrayCountOn working!              V\n");
	}
	else
	{
		printf("BitArrayCountOn NOT working!          X\n");
	}
}

static void TestCountOnNoLoop()
{
	bitarray_t test = 150;
	size_t num = BitArrayCountOnNoLoop(test);
	if (num == 4)
	{
		printf("BitArrayCountOnNoLoop working!        V\n");
	}
	else
	{
		printf("BitArrayCountOnNoLoop NOT working!    X\n");
	}
}

static void TestCountOnLUT()
{
	bitarray_t test = 150;
	size_t num = BitArrayCountOnLUT(test);
	if (num == 4)
	{
		printf("BitArrayCountOnLUT working!           V\n");
	}
	else
	{
		printf("BitArrayCountOnLUT NOT working!       X\n");
	}
}

static void TestCountOff()
{
	bitarray_t test = 150;
	size_t num = BitArrayCountOff(test);
	if (num == 60)
	{
		printf("BitArrayCountOff working!             V\n");
	}
	else
	{
		printf("BitArrayCountOff NOT working!         X\n");
	}
}

static void TestAllFuncs()
{
	TestSetAll();
	TestResetAll();
	TestGetVal();
	TestSetBit();
	TestSetOn();
	TestSetOff();
	TestFlip();
	TestRotR();
	TestRotL();
	TestMirror();
	TestMirrorNoLoop();
	TestMirrorLUT();
	TestCountOn();
	TestCountOnNoLoop();
	TestCountOnLUT();
	TestCountOff();
}
