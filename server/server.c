#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT "3490"
int main()
{
	char server_message[256] = "You have reached the server";
	struct addrinfo hints, *res;
	int status, server_socket, client_socket;

	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	if( (status = getaddrinfo(NULL, SERVER_PORT, &hints, &res)) !=0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	if( (server_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) !=0 )
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return 2;
	}

	if ( bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address) == -1 )
	{
		fprintf(stderr, "bind: %s\n", strerror(errno));
		return 3;
	}

	if ( listen(server_socket, 1) == -1)
	{
		fprintf(stderr, "listen: %s\n", strerror(errno));
		return 3;
	}
	
	for (int i = 0; i<5; i++)
	{
		if ( (client_socket = accept(server_socket, NULL, NULL)) == -1)	
		{
			fprintf(stderr, "recv: %s\n", strerror(errno));
			return 4;
		}

		if ( send(client_socket, server_message, sizeof(server_message), 0) == -1)
		{
			fprintf(stderr, "send: %s\n", strerror(errno));
			return 5;
		}
	}
	

	freeaddrinfo(res);
	close(server_socket);
	return 0;
}