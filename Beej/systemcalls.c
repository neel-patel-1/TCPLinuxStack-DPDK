#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

int main()
	int status;

	struct addrinfo hints;
	struct addrinfo *servinfo;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_falgs = AI_PASSIVE;

	if ( (status = getaddrinfo(NULL, "3490", &hints, &servinfo)) !=0)
	{

		printf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}



	freeaddrinfo(servinfo);
}
