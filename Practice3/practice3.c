/** 	Eric Altenburg
* 	12 September 2019
* 	I pledge my honor that I have abided by the Stevens Honor System.
**/

#include<stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int val_in, val_out;
	
	char str_in[10], str_out[10];
	
	scanf("%d", &val_in);
	sprintf(str_out, "%d", val_in); //str is array keeping string, %d specifier, var_0 interger
	printf("Int to String: %s \n", str_out);	

	scanf("%s", str_in);	
	val_out = atoi(str_in);	
	printf("\nString to Int: %d \n", val_out);
	return 0;
}
