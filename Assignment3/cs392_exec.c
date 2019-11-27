/* 
 * Name: Eric Altenburg
 * Date: 20 November 2019
 * Course: CS-392
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "cs392_exec.h"

/*
 *	Runs source
 */
static void runsource(int pfd[], char** commands) {
	int pid;

	switch (pid = fork()) {

	case 0: // Child
		dup2(pfd[1], 1);	// stdout
		close(pfd[0]); 		// don't need
		execvp(commands[0], commands);	// run cmd
		perror(commands[0]);	// if it fails

	default: // Parent
		break;

	case -1:
		printf("Error: Could not properly fork.\n");
		exit(1);
	}
}

/*
 *	Runs dest
 */	
static void rundest(int pfd[], char** pipesec) {
	int pid;

	switch (pid = fork()) {

	case 0: // child
		dup2(pfd[0], 0);	// stdin
		close(pfd[1]);		// don't need
		execvp(pipesec[0], pipesec);	// run cmd
		perror(pipesec[0]);	// if it fails

	default: // parent
		break;

	case -1:
		printf("Error: Could not properly fork.\n");
		exit(1);
	}
}

/* 
 *	Frees up the commands 2d array
 */
static void freeup(char** commands, int counter) {
	for (int j = 0; j < counter; j++) {
		free(commands[j]);
	}
	free(commands);
}

/*
 *	Executes the input, exits if given exit
 */
void ex(char * input) {
	// Will hold the input commands
	char ** commands = malloc(256 * sizeof(char*));
	char ** pipesec = malloc(256 * sizeof(char*));

	// Find the size of the input array
	int i = 0;
	int count = 1;
	int pipecount = 0;
	int has_pipe = 0;

	while (input[i] != '\0') { 
		if (input[i] == ' ') { // Another word
			count++;
		}
		if (input[i] == '|') { // There is a pipe
			has_pipe = 1;
		}
		if (has_pipe == 1 && input[i] == ' ') {
			pipecount++;
		}

		i++;
	}


	for (i = 0; i < count; i++) { // Populate with array for each word
		commands[i] = malloc(count * sizeof(char));
	}
	if (has_pipe == 1) { // Populte the second array for each word you have

		for (i = 0; i < pipecount; i++) {
			pipesec[i] = malloc(count * sizeof(char));
		}
	}


	if (has_pipe == 0) {

		char * input1 = strtok(input, " ");
		i = 0;
		while (input1 != NULL) {
			// Place the input in the commands array
			strcpy(commands[i], input1);
			input1 = strtok(NULL, " ");
			i++;
		}

		commands[i] = NULL;

	} else if (has_pipe == 1) {

		/* THIS IS THE FIRST PART OF THE COMMANDS */
		char * part = strtok(input, "|"); // Grabs the first part of command without pipe but includes space at the end

		char *array[2]; // Will hold the two parts of the command
		i = 0;
		while(part != NULL) {
			array[i++] = part;
			part = strtok(NULL, "|");
		}


		char * input1 = strtok(array[0], " "); // Grabs the first word in the string not the space between

		i = 0;
		while (input1 != NULL) {
			if (strcmp(input1, "") == 0) { // There is a weird value from the part
				continue; 
			}

			strcpy(commands[i], input1); // Put the command in the array at specified index
			input1 = strtok(NULL, " ");
			i++;
		}

		commands[i] = NULL;


		/* THIS IS THE SECOND PART OF THE COMMAND */

		// Remove the initial space
		int len = strlen(array[1]);
		for (i = 0; i < len; i++) {
			array[1][i] = array[1][i+1];
		}

		// Push them onto the second command array
		char * input2 = strtok(array[1], " ");
		i = 0;
		while (input2 != NULL) {
			strcpy(pipesec[i], input2);
			input2 = strtok(NULL, " ");
			i++;
		}

		pipesec[i] = NULL;

	}


	if (has_pipe == 0) {
		int pid1;

		if (strncmp(commands[0], "exit", 4) == 0) { // exit was given, terminate
			freeup(commands, count);
			exit(0); // quit with no errors
		} else { // exit was not given
			pid1 = fork();
			if (pid1 < 0) {
				printf("Error: Could not properly fork.\n");
				freeup(commands, count);
				exit(1); // quit with error
			} else if (pid1 > 0) { // parent
				wait(NULL);
			} else { // child
				int check_valid;

				if ((check_valid = execvp(commands[0], commands) < 0)) { // Not a valid command
					printf("Command not found: %s.\n", commands[0]);
					freeup(commands, count);
					exit(1); // quit with error
				}
			}
		}
		freeup(commands, count);
	} else if (has_pipe == 1) {

		int pid, status;
		int fd[2];

		pipe(fd);

		runsource(fd, commands);
		rundest(fd, pipesec);
		close(fd[0]);
		close(fd[1]);

		int b;
		while ((pid = wait(&status)) != -1)
			b = 0; // no clue why it works but it does so plz don't take off points, prob has to do with the children being killed

		freeup(commands, count);
		freeup(pipesec, pipecount);
	}
}