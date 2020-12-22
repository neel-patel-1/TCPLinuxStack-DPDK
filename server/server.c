#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define SERVER_PORT "3490"
#define CLOCK_TYPE CLOCK_PROCESS_CPUTIME_ID

struct timespec diff(struct timespec start, struct timespec end);
int main()
{
	//char server_message[256] = "You have reached the server";
	struct timespec server_message, before, after;
	struct addrinfo hints, *res;
	struct sockaddr_storage clientAddress;
	socklen_t clientAddressLength;
	int status, server_socket, client_socket;

	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(NULL, SERVER_PORT, &hints, &res)) !=0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	if( (server_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) ==-1 )
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return 2;
	}

	if ( bind(server_socket, res->ai_addr, res->ai_addrlen) == -1 )
	{
		fprintf(stderr, "bind: %s\n", strerror(errno));
		return 3;
	}

	
	if ( listen(server_socket, 1) == -1)
	{
		fprintf(stderr, "listen: %s\n", strerror(errno));
		return 4;
	}
	
	for (int i = 0; i<5; i++)
	{
		clock_gettime(CLOCK_TYPE, &before);
		if ( (client_socket = accept(server_socket, (struct sockaddr*)&clientAddress, &clientAddressLength)) == -1)	
		{
			fprintf(stderr, "recv: %s\n", strerror(errno));
			return 5;
		}

		clock_gettime(CLOCK_TYPE, &after);
		server_message = diff(before, after);
		if ( send(client_socket, &server_message, sizeof(server_message), 0) == -1)
		{
			fprintf(stderr, "send: %s\n", strerror(errno));
			return 6;
		}
	}
	

	freeaddrinfo(res);
	close(server_socket);
	return 0;
}
struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}