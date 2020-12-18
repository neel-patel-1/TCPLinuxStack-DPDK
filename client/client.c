#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <errno.h>
#include <string.h>
 
/*
int main()
{
	char serverIPAddress[15] = "127.000.000.001";
	//create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);	
	
	//connect to another socket (using connect function)
	//first specify an address to connect to
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	if(inet_pton(AF_INET, serverIPAddress, &(server_address.sin_addr))<0)
	{
		printf("Server address could not be resolved\n");
		return 1;
	}
	//value of 0 is success, -1 is a fail
	int connection = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	if(connection == -1)
	{
		printf("Connection failed with errno: %d\n", errno);
		return 2;
	}

	char server_response[256];	
	recv(network_socket, &server_response, sizeof(server_response), 0);

	printf("The server sent the data: %s \n", server_response);
	
	//close the socket
	close(network_socket);
	return 0;
}*/
//pass in args from command line for benchmark
//server should accept incoming connections and send some kind
//of information back to the client
//client should measure latency
#define MSG_LENGTH 28
#define SERVER_IPv4 "127.0.0.1"
#define SERVER_IPv6 "::1"
#define SERVER_PORT "3490"
#define ITERATIONS 5
int main()
{
	int status, sockfd, numBytes;
	struct addrinfo hints, *res;
	char server_response[MSG_LENGTH];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if( (status = getaddrinfo(SERVER_IPv4, SERVER_PORT, &hints, &res)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	if ( (sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
	}

	printf("Testing...\n");
	for(int i=0; i<ITERATIONS; i++)
	{
		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1)
		{
			fprintf(stderr, "connect: %s\n ", strerror(errno));
			return 2;
		}
		numBytes = recv(sockfd, &server_response, sizeof(server_response), 0);

		if( numBytes == -1 )
		{
			fprintf(stderr, "recv: %s\n", strerror(errno));
		}
		else 
		{
			printf("Latency: %s\n", server_response);
		}
	}

	close(sockfd);
}
