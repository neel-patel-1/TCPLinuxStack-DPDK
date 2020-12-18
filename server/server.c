#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#include <netinet/in.h>

#define SERVER_PORT 3490
int main()
{
	char server_message[27] = "You have reached the server";
	
	//initialize server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to out specified IP and port
	if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1)
	{
		printf("Bind failed with errno:%d\n ", errno);
		return 1;
	}
	
	//listen for connections
	if(listen(server_socket, 1) == -1)
	{
		printf("Listen failed with errno:%d\n", errno);
		return 2;
	}
	
	//initialize client socket we can send data to
	int client_socket;
	if (client_socket = accept(server_socket, NULL, NULL) == -1)
	{
		printf("Accept failed with errno:%d\n", errno);
	}	

	//send our server message
	send(client_socket, server_message, sizeof(server_message), 0);

	//close the socket
	close(server_socket);
	return 0;
}
/*
int yes=1;
2 //char yes='1'; // Solaris people use this
3
4 // lose the pesky "Address already in use" error message
SYSTEM CALLS OR BUST 24
5 if (setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
6 perror("setsockopt");
7 exit(1);
8 }
*/
//possible fix for server malfunction
