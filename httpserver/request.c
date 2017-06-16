#include <stdio.h>
#include <string.h>
#include "session.h"

int http_request(ClientSession *session)
{
	int		ret;
	int		len;
	char	buffer[1024] = {'\0'};

	memset(session->readbuf, 0, 2048);
	len = read(session->fd, session->readbuf, 1203);
	if(len < 0)
	{
		return -1;
	}
	else if(len == 0)
	{
		printf("client close\n");
		session->state = 1;
		return 1;
	}
	else
	{
		fprintf(stderr, "READ:\n%s\n", session->readbuf);
	}

	if(strncmp(session->readbuf, "GET", 3) == 0)
	{
		http_request_get(session);
	}

	if(strncmp(session->readbuf, "POST", 4) == 0)
	{
		http_request_post(session);
	}

	return 0;
}

/* 处理GET请求 */
int http_request_get(ClientSession *session)
{
	int		i = 0, j=0;
	char	getdata[101] = {'\0'};
	i = 4;
	while(session->readbuf[i] != 0x20)
	{
		getdata[j++] = session->readbuf[i++];
	}
	
	printf("GetData: %s\n", getdata);

	if(strcmp(&getdata[1], "favicon.ico") == 0)
		session->state = 2;

	return 0;
}

/* 处理POST请求 */
int http_request_post(ClientSession *session)
{
	return 0;
}

