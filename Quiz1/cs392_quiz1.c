/**	I pledge my honor that I have abided by the Stevens Honor System.
 *	Eric Altenburg
 *	26 September 2019
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** arv) {
	// This produces a seg fault, and although I couldn't find it, I believe that it is due to
	// me trying to copy into the buffer, however, I am copying possibly too much,
	// therefore, when I try to write it to the file, it is trying to write something that doesn't exist
	// which will produce the seg fault. Not entirely sure if this is true, but this is what makes the most sense to me. 

	FILE *fp1; // File we are opening
	fp1 = fopen("argv[1]", "r"); // Opens the file

	fseek(fp1, 0, SEEK_END); // Seek to the end of the file
	size_t size = ftell(fp1); // get the current file pointer
	//fseek(fp1, 0, SEEK_SET); // Seek back to the beginning
	rewind(fp1); // Rewind back to the beginning
	char *buffer = malloc(size+1); // Allocate a buffer of the correct size

	char *line_buffer = malloc(size+1);

	while(fgets(line_buffer, 81, fp1) != NULL) {
		int length = strlen(line_buffer);
		memcpy(buffer, line_buffer, length);
	}

	FILE *fp2;
	fp2 = fopen("quiz1.log", "w");
	fwrite(buffer, size, 1, fp2);

	fclose(fp1);
	fclose(fp2);

	return 0;
}