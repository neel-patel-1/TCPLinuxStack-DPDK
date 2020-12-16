#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


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
		exit(1);
	}
	//value of 0 is success, -1 is a fail
	int connection = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	if(connection == -1)
	{
		printf("Connection error\n");
	}

	char server_response[256];	
	recv(network_socket, &server_response, sizeof(server_response), 0);

	printf("The server sent the data: %s \n", server_response);
	
	//close the socket
	close(network_socket);
	return 0;
}
