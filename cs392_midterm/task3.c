#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cs392_file_insert(char * path, int index, char * str){

	/* Please write down your code here
	 *
	 * You can use whatever API you want to use
	 * You can allocate whatever memory you want 
	 * Please do error handling checks 
	 * 
	 * Please write down your pledge of honor system as comment 
	 *
	 * */

	FILE *file = fopen(path, "w");
	char * buff = malloc(sizeof(str));

	fseek(file, index, 0);
	
	
	// Ran oout of time on 2 becuase of size_t issue, but basicaly I wanted to open the file and then create a buffer, seek to the position in the file, write to that position. close file.

	return 0;
}


int main(int argc, char ** argv){

	cs392_file_insert("cs392_task3_tmp.txt", 10, "@cs392 data inserted@");

	return 0;
}


