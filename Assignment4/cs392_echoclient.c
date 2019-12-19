/*
 *	I pledge my honor that I have abided by the Stevens Honor System. -Eric Altenburg
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/select.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>

pthread_mutex_t lock;

void logger(char *);

void * cs392_connect (void * arguments) {
	int s;
	char ** input = (char **) arguments;
	char buffer[1024];
	struct sockaddr_in echoserver;
	
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		perror("Error: Socket");
		exit(EXIT_FAILURE);
	}

	memset(&echoserver, 0, sizeof(echoserver));
	echoserver.sin_family = AF_INET;
	echoserver.sin_addr.s_addr = inet_addr(input[1]);
	echoserver.sin_port = htons(atoi(input[2]));

	if (connect(s, (struct sockaddr *) &echoserver, sizeof(echoserver)) == -1) { // Check to see if error for connect
		perror("Error: connect");
		exit(EXIT_FAILURE);
	}

	fgets(buffer, 1024, stdin);

	if (send(s, buffer, 1024, 0) < 0) { // Checking the error for the send
		perror("Error: send");
		exit(EXIT_FAILURE);
	}

	if (recv(s, buffer, 1023, 0) < 0) { // Checking the error for the recv
		perror("Error: recv");
		exit(EXIT_FAILURE);
	}

	logger(buffer);
	printf("%s\n", buffer);

	if (close(s) < 0) { // Checking the error for the close
		perror("Error: close");
		exit(EXIT_FAILURE);
	}

	pthread_exit(NULL);
}

/*
 *	Writes to file
 */
void logger (char * input) {
	FILE *fp;
	pthread_mutex_lock(&lock);

	fp = fopen("cs392_socket.log", "a"); // append

	if (fp == NULL) { // Checking the error for the fopen
		perror("Error: fopen");
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "%s", input);
	fclose(fp);
	pthread_mutex_unlock(&lock);
}	

int main (int argc, char * argv[]) {
	if(argc != 4) { // Checking usage
		perror("Usage: Invalid argument");
		exit(EXIT_FAILURE);
	}

	pthread_t *t;
	int n = atoi(argv[3]);

	if (n <= 0) { // Negative
		perror("Negative threads");
		exit(EXIT_FAILURE);
	}

	// Dynamically allocated pthread_t array
    pthread_t *threads;
    threads = (pthread_t *) malloc(sizeof(pthread_t) * n);

    // Create n amount of threads
    for (int i = 0; i < n; i++) {
    	pthread_create(&threads[i], NULL, &cs392_connect, (void *) argv);
    }

    // Join
    for (int i = 0; i < n; i++) {
    	pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
    
    return 0;
}