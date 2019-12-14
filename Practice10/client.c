/**
 *	I pledge my honor that I have abided by the Stevens Honor System.
 *  Eric Altenburg
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ     27

/* You are required to implement the main function: 
	Step 1: get and attach to a piece of shared memory created by server.c. The key string of the shared memory is "cs392_key" and the size is 27; 
	Step 2: print the string which starts from the first byte in the shared memory. Please print to the standard output 
	Step 3: change the first byte of the shared memory to "*"
	Step 4: dettach from the shared memory and then return; 
	Step 5: run "make". If your code is correct, you will be able to see "Congratulations! You Win!"
 */

int main(int argc, char ** argv){
	char *shmem;
	int shmemid;
	char c;
	key_t k = ftok("cs392_key", 0);

	if ((shmemid = shmget(k, SHMSZ, IPC_CREAT | 0666)) < 0) { // Error checking
		printf("shmget error");
		exit(1);
	}

	if ((shmem = shmat(shmemid, NULL, 0)) == (char*) -1) { // Error checking
		printf("shmat error");
		exit(1);
	}

	char * x = (char*) shmat(shmemid, (void*) 0, 0);

	printf("%s\n", x);

	shmem[0] = '*';

	shmdt(shmem);

    return 0;
}
