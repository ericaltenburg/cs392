/* 
 * Name: Eric Altenburg
 * Date: 20 November 2019
 * Course: CS-392
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <stdlib.h>
#include "cs392_exec.h"
#include "cs392_log.h"
#include "cs392_signal.h"

/*
 *	Prints out the shell text, waits for input, calls the method. If given the exit, it will terminate.
 *	Resets the memory after.
 */
int main() {
	// Variables
	char buffer[256];
	int input;

	// Continually run, checking the input
	for(;;) { // Weird while true loop I found that uses a for loop, it looked cooler than while(1) so I used it
		handles();
		// Initial statement
		printf("cs392_shell $: ");
		fflush(stdout);

		input = read(0, buffer, 255);
		if(input < 0) {
			if (errno == EINTR) { // check errno
				continue;
			} else {
				printf("Could not read input.\n");
				exit(1);
			}
		}

		// Set terminatin symbol in buffer for readind in exec.c
		buffer[input-1] = '\0';
		write_to_file(buffer);
		ex(buffer);
	}

	return 0;
}
