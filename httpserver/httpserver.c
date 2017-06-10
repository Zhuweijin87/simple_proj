#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

/* 建立监听 */
int socket_listen(char *ipaddr, int port)
{
	int		ret;
	int		sockfd;
	struct  sockaddr_in	server;
#if 0
	int		port;
	char	ipaddr[20] = {'\0'};


	ret = sscanf(addr, "[^:]:%d", ipaddr, &port);
#endif
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("socket eror: %d,%s\n", ret, strerror(errno));
		return -1;
	}	

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ipaddr);

	int opt = 1;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if(ret == -1)
	{
		printf("setsockopt SO_REUSEADDR: %d,%s\n", ret, strerror(ret));
		close(sockfd);
		return -1;
	}

	ret = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	if(ret == -1)
	{
		printf("bind error: %d,%s\n", ret, strerror(errno));
		close(sockfd);
		return -1;
	}

	ret = listen(sockfd, 20);
	if(ret == -1)
	{
		printf("listen error: %d, %s\n", ret, strerror(errno));
		close(sockfd);
		return -1;
	}
	return sockfd;
}

int socket_accept(int sockfd)
{
	int		ret, c;
	struct  sockaddr_in  client;
	socklen_t	clitlen;
	
	while(1)
	{
		clitlen = sizeof(client);
		c = accept(sockfd, (struct sockaddr *)&client, &clitlen);
		if(c == -1)
		{
			printf("accpet error:%d,%s\n", ret, strerror(errno));
			return -1;
		}

		http_handle(c);
	}

	return 0;
}

/* 处理网页request与response */
int http_handle(int c)
{
	http_read(c);
	http_write(c);
	
	sleep(1);
	close(c);
	return 0;
}

int main()
{
	int		sockfd;
	
	sockfd = socket_listen("192.168.92.130", 8001);
	if(sockfd == -1)
	{
		return -1;
	}

	socket_accept(sockfd);

	return 0;
}
