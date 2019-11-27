/*
 * Eric Altenburg
 * I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t pid;
	


	pid = fork();
	if (pid < 0) {
		perror("Fork");
		return -1;
	} else if (pid == 0) { // Child process
		printf("Hello from child\n");
	} else { // Parent process
		printf("This is the PID of the child: %d\n", pid);
		while (1) {
			sleep(5);
			printf("Hello from parent\n");
		}
	}

	return 1;
}