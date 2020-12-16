#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void serverListen()
{
	//Server listening on host IP address on port 3490
	int status;

	struct addrinfo hints;
	struct addrinfo *servinfo;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ( (status = getaddrinfo(NULL, "3490", &hints, &servinfo)) !=0)
	{

		printf("getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
	freeaddrinfo(servinfo);
}

void clientConnect()
{
	//client wanting to connect to a server on port 3490
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo; //points to linked list of results

	memset(&hints, 0, sizeof hints);//struct is empty
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);


	freeaddrinfo(servinfo);
}

void printIPAddresses()
{
	struct addrinfo hints, *res, *p;
	int status;
}
int main()
{

	
}
