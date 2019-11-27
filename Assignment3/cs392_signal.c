/* 
 * Name: Eric Altenburg
 * Date: 20 November 2019
 * Course: CS-392
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "cs392_signal.h"

/*
 *	Checks for SIGINT and SIGTSTP, then prints to show that the command was recieved
 */
void hdl(int sig, siginfo_t *siginfo, void *context) {
	if (sig == SIGINT) {
		printf(" Signal received: %d. To terminate the process, type exit.\n", sig);
	}
	if (sig == SIGTSTP) {
		printf(" Signal received: %d. To terminate the process, type exit.\n", sig);
	}
}

/*
 *	Sets the flags then calls the functions to handle them
 */
void handles() {
	struct sigaction act;

	memset(&act, '\0', sizeof(act));

	act.sa_sigaction = &hdl;
	act.sa_flags = SA_SIGINFO;

	if ((sigaction(SIGINT, &act, NULL) < 0) || (sigaction(SIGTSTP, &act, NULL) < 0)) {
		perror("Sigaction error.\n");
	}
}

