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

void printIPAddresses(int argc, char *argv[])
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if(argc !=2)
	{
		fprintf(stderr, "usage: showip hostname\n");
		return 1
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( status = getaddrinfo(argv[1], NULL, &hints, &res) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
	}
	printf("IP addresses for %s:\n\n", argv[1]);
	for(p = res; p!=NULL; p=p->ai_next)
	{
		void *addr;
		char *ipver;

		if(p->ai_family == AF_INET)
		{
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else
		{
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}
		inet_ntop(p->aifamily, addr, ipstr, sizeof ipstr);
		printf(" %s: %s\n", ipver, ipstr);
	}
	freeaddrinfo(res);
}
void bindListenSocket()
{
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //auto-fill IP
	getaddrinfo(NULL, "3490", &hints, *res);// socket to be bound to port 3490
	
	int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	//create a socket using info from results ptr

	bind(sockfd, res->ai_addr, res->ai_addrlen);
	//bind the socket to the correct port
	listen(sockfd, 5);//listen on sockfd (port 3490) for incoming connections

	//accepted connection is assigned a new file descriptor
	struct sockaddr_storage their_addr;
	socklen_t addr_size = sizeof their_addr;
	int newfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

	char *msg = "You have contacted the server.\n";
	int len = strlen(msg);
	int bytes_sent = send(newfd, msg, len, 0);

	close(sockfd);
}
void connectSocket()
{
	struct addrinfo hints, *res;
	int sockfd;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo("www.example.com", "3490", &hints, &res);

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	connect(sockfd, res->ai_addr, res->ai_addrlen); //returns -1 on error
}
int main(int argc, char *argv[])
{
	printIPAddresses(argc, argv);
	
}
