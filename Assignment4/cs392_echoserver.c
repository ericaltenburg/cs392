/*
 *	I pledge my honor that I have abided by the Stevens Honor System. -Eric Altenburg
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/select.h>

int main(int argc, char ** argv) {
	 if (argc != 2) { // incorrect amount of arguments supplied
	 	perror("Usage: Invalid argument");
	 	exit(EXIT_FAILURE);
	 }

	int s, c, n;
	char buffer[1024];
	struct sockaddr_in echoserver, echoclient;
	fd_set active_fd_set, read_fd_set;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) { // Error creating socket
		perror("Error: Socket creation");
		exit(EXIT_FAILURE);
	}

	memset(&echoserver, 0, sizeof(echoserver));
	echoserver.sin_family = AF_INET;
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
	echoserver.sin_port = htons(atoi(argv[1]));

	if (bind(s, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) { // Error binding
		perror("Error: Bind");
		exit(EXIT_FAILURE);
	}

	if (listen(s, 1) < 0) { // Error listening
		perror("Error: Listening");
		exit(EXIT_FAILURE);
	}

	FD_ZERO(&active_fd_set);
	FD_SET(s, &active_fd_set);

	int connection;

	for(;;) {
		read_fd_set = active_fd_set;

		if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) { // Error select
			perror("Error: Select");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < FD_SETSIZE; ++i) {
			if (FD_ISSET(i, &read_fd_set)) {

				if (i == s) {
					n = sizeof(echoclient);
					connection = accept(s, (struct sockaddr *) &echoclient, &n);
					
					if (connection < 0) {
						perror("Error");
						exit(EXIT_FAILURE);
					}

					FD_SET(connection, &active_fd_set);
				} else {

					if (recv(i, buffer, 1024, 0) < 0) {
						perror("Error");
						exit(EXIT_FAILURE);
					}

					if (send(i, buffer, 1023, 0) < 0) {
						perror("Error");
						exit(EXIT_FAILURE);
					}

					if (close(i) < 0) {
						perror("Error");
						exit(EXIT_FAILURE);
					}

					FD_CLR(i, &active_fd_set);
				}
			}
		}
	}

	return 0;
}