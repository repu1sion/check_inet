//gcc check_inet.c -o check_inet && ./check_inet

//this utility check internet connection by connecting to 8.8.8.8 host on port 443

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

	int rv;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = { AF_INET, htons(443), inet_addr("8.8.8.8") };

	//setting timeout 1 second
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));

	if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) != 0)
	{
		printf("fail\n");
		rv = 1;
	}
	else
	{
		printf("ok\n");
		rv = 0;
	}
	close(sockfd);
	return rv;
}
