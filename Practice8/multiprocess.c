/* I pledge my honor that I have abided by the Stevens Honor System.
 * Eric Altenburg
 */

/*
 * This program implements a multi-process program:
 *Functionality Description:
 This program will receive a string from the command line. The string is ensured to be shorter than 1024 bytes
 In the parent process, the received string will be logged into a file called "cs_392_test.log"
 In the child process, the received string will be printed to the standard output
 *
 * Testing points:
 Please figure out compiling and linking issues that prevent the program from building
 	Please check compiler warnings as well

 Please find syntax and grammar errors that also prevent the building
 Please find the errors that mismatch the above descriptions
 Please find the missing of error checking

 Hinis are marked across the code
 *
 */





#include <stdlib.h>
//hint 1
#include <stdio.h>
#include <sys/types.h>
//hint 2:
#include <unistd.h>



//hint 3
int main (int argc, char** argv){

	int pid;

	//hint 4
	char buffer[1024];

	//hint 5
	scanf("%s", buffer);

	pid = fork();
	//hint 6: missing checks?
	if (pid < 0) {
		printf("Error: Problem with forking.");
		return 1;
	}


	if (pid > 0) { // parent process //hint 7

		FILE *fptr;

		printf("I am the parent, return from fork, child pid=%d\n", pid);

		//hint 8
		fptr = fopen("cs_392_test.log", "a");

		if(fptr == NULL){
			printf("Error!");
			exit(1);
		}

		//hint 9
		fprintf(fptr,"%s",buffer);
		fclose(fptr);

		//wait(pid);

	}else if (pid == 0){ // child process
		printf("I am the child, the message received is %s\n", buffer);

		//hint 10: maybe do some cleanup?

	}
	return 0;
}
