/**
Author:			Eric Altenburg
Date: 			5 September 2019
Description:	Adding 1 to 10000000
**/

#include <stdio.h>

int main(int argc, char ** argv) {
	unsigned long sum;
	sum = 0;	

	for (int i = 1; i <= 10000000; ++i)
		sum = sum + i;

	printf("The final value is %lu ", sum);

	return 0;
}
