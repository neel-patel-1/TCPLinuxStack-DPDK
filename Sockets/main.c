#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAXLINE 4096
#define IP_ADDR  "127.0.0.1"
#define SERV_PORT  9877
/*
 * Connectionless UDP server implementing l2fwd
 * client will send datagrams usin UDP protocol
 * server receives datagram (using recvfrom() ??)
 * 
 * IDEA: find way to measure len of first packet; assume all next packets are same length
 */
struct sockaddr_in *pcliaddr;//client address
void echo(int sockfd, struct sockaddr *pcliaddr, int len)
{
	int n;
	char mesg[len];
	for(;;){
		n = recvfrom(sockfd, mesg, 8, 0, pcliaddr, sizeof(&pcliaddr));
		sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}
void init(int sockfd, struct sockaddr *pcliaddr){
	int len;
	char message[MAXLINE];
	len = recvfrom(sockfd, message, 0, MAXLINE, pcliaddr, sizeof(&pcliaddr));
	echo(sockfd, pcliaddr, len);
}
int main(){
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));	
	servaddr.sin_family - AF_INET;
	servaddr.sin_addr.s_addr = htonl(IP_ADDR);
	servaddr.sin_port = htons(SERV_PORT);

	bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	init(sockfd, (struct sockaddr*) &cliaddr);

}
