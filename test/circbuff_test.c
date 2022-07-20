#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "../include/circbuff.h"

void TestAllFuncs();

int main()
{
	TestAllFuncs();
	return (0);
}

void TestAllFuncs()
{
	char str1[15] = "some string hi";
	char to_cmp1[15] = " ";
	char str2[70] = "i know my strings are weird...on the other hand they are userfull";
	char second_half[32] = "on the other hand they are use";
	char to_cmp2[34] = " ";
	int bil = 1001001001;
	int int_cmp = 0;
	size_t bilandsome = 1002003004;
	size_t sizet_cmp = 0;
	
	circbuff_ptr_t circbuff = CircBuffCreate(30);
	
	if(NULL != circbuff)
    {
    	printf("CircBuffCreate working!                              V\n");
	}
	else
	{
		printf("CircBuffCreate NOT working!                          X\n");
	}
	
	
	CircBuffWrite(circbuff, (const void*)str1, 13);
	
    if(13 == CircBuffSize(circbuff))
    {
    	printf("CircBuffSize & CircBuffWrite working!                V\n");
	}
	else
	{
		printf("CircBuffSize & CircBuffWrite NOT working!            X\n");
	}
	
	if(17 == CircBuffFreeSpace(circbuff))
    {
    	printf("CircBuffFreeSpace working!                           V\n");
	}
	else
	{
		printf("CircBuffFreeSpace NOT working!                       X\n");
	}
	
	CircBuffRead(circbuff, to_cmp1, 13);
	
	if(0 == strncmp(to_cmp1, str1, 13))
    {
    	printf("CircBuffRead working!                                V\n");
	}
	else
	{
		printf("CircBuffRead NOT working!                            X\n");
	}
	
	CircBuffWrite(circbuff, (const void*)str2, 60);
	
	if(!CircBuffIsEmpty(circbuff))
    {
    	printf("CircBuffIsEmpty working!                             V\n");
	}
	else
	{
		printf("CircBuffIsEmpty NOT working!                         X\n");
	}
	
	CircBuffRead(circbuff, to_cmp2, 33);
	
	CircBuffWrite(circbuff, (const void*)&bil, 4);
	CircBuffRead(circbuff, (void*)&int_cmp, 4);
	
	CircBuffWrite(circbuff, (const void*)&bilandsome, 8);
	CircBuffRead(circbuff, (void*)&sizet_cmp, 8);
	
	if((0 == strcmp(to_cmp2, second_half)) && 
	(bil == int_cmp) && (bilandsome == sizet_cmp))
	{
    	printf("Edge case passed!                                    V\n");
	}
	else
	{
		printf("Edge case NOT passed!                                X\n");
	}
	
	
	printf(" ~ Run vlg to check CircBuffDestroy! ~ \n");
	printf("       ~ END OF TEST FUNCTION ~\n");
	
	CircBuffDestroy(circbuff);
}
















