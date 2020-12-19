#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <errno.h>
#include <string.h>
#include <time.h>

#define MSG_LENGTH 28
#define SERVER_IPv4 "127.0.0.1"
#define SERVER_IPv6 "::1"
#define SERVER_PORT "3490"
#define ITERATIONS 5
#define CLOCK_TYPE CLOCK_PROCESS_CPUTIME_ID
//unsure of which clock type to use

timespec diff(timespec start, timespec end);
int main()
{
	int status, sockfd, numBytes;
	struct addrinfo hints, *res;
	struct timespec before, after, difference;
	char server_response[MSG_LENGTH];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(SERVER_IPv4, SERVER_PORT, &hints, &res)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	if ( (sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return 2;
	}

	printf("Testing...\n");
	for(int i=0; i<ITERATIONS; i++)
	{
		clock_gettime(CLOCK_TYPE, &before);
		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1)
		{
			fprintf(stderr, "connect: %s\n ", strerror(errno));
			return 3;
		}
		numBytes = recv(sockfd, &server_response, sizeof(server_response), 0);
		clock_gettime(CLOCK_TYPE, &after);
		if( numBytes == -1 )
		{
			fprintf(stderr, "recv: %s\n", strerror(errno));
			return 4;
		}
		else 
		{
			difference = difftime(before, after);
			printf("Latency (server-side): %s , RTT: %d:%ld\n", server_response, difference.tv_sec, difference.tv_nsec);
		}
	}
	freeaddrinfo(res);
	close(sockfd);
}
timespec diff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}