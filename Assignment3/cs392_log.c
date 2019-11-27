/* 
 * Name: Eric Altenburg
 * Date: 20 November 2019
 * Course: CS-392
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include "cs392_log.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *	Writes each command (and the options) to “cs392_shell.log” in the manner of appending. 
 *	If “cs392_shell.log” does not exist, this function should create that file in the 
 *	current working directory.
 */
void write_to_file(char * input) {
	// fopen with append file access mode
	FILE *fp = fopen("cs392_shell.log", "a");

	if (fp == NULL) { // Error checking
		perror("Error: Could not open the file.\n");
	} else { // Write
		fprintf(fp, "%s\n", input);
	}

	// Close the file
	fclose(fp);
}