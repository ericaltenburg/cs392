/* I pledge my honor that I have abided by the Stevens Honor System.
 * Eric Altenburg
 */


#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 


/* Requirement: 
 *	You are required to implement a function called getwebpage
 *	This function will retrive the data from a specified webpage and save the data to a specified file
 *	getwebpage takes two argument: a "url" and a "filepath". The "url" represents the url of the website (e.g., www.google.com); the "filepath" is the path of a file which you will create and save the data you get from the webpage *

 */

void getwebpage(char *url, char * filepath)
{

	char http_request[1024];
	struct hostent *host;
	int sockfd;
	struct sockaddr_in destAddr;
	char buffer[1024];
	int cnt;
	FILE*fp;

	/* Hint 1: how to convert url to IP related information*/
    host = gethostbyname(url);
    if (!host) {
    	printf("%s was not resolved\n", url);
    	exit(1);
    }

    destAddr.sin_family = PF_INET;
	destAddr.sin_port = htons(80); // HTTP port is 80 // copy
	destAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr); // copy

	memset(&(destAddr.sin_zero), 0, 8);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(connect(sockfd, (struct sockaddr *) &destAddr, sizeof(struct sockaddr)) == -1) {
		fprintf(stderr, "Error, with client connecting to server\n");
		close(sockfd);
		return;
	}

	memset(http_request, ' ', sizeof(http_request));
    strcpy(http_request,"GET / HTTP/1.1\r\nHost: ");
    strcat(http_request,url);
    strcat(http_request,"\r\nConnection: close\r\n\r\n");

    send(sockfd, http_request, strlen(http_request), 0);

    fp = fopen(filepath, "w");

    while(cnt = recv(sockfd, buffer, 1024, 0)) {
    	fwrite(buffer, 1, cnt, fp);
    	continue;
    }

    fclose(fp);




	/*Hint 2: set up address for socket*/

	/* more code here ..........*/

	/*Hint 3: set up request to the server*/

	/* more code here ..........*/    

	/* Hint 4: how to keep receiving data until its end*/
	// ssize_t cnt;
	// while(cnt = recv(serversock, http_request, http_request-1, 0)) {
	// 	 more code here .. 	........     
	// 	fprintf(fp, "%s", http_request);
	// 	continue;
	// }
	// fclose(fp);
}


int main(int argc, char** argv){
	getwebpage(argv[1], argv[2]);
}
