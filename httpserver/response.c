#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "session.h"

int http_response(ClientSession *session)
{
	int		ret;
	char	buffer[1024] = {'\0'};

	if(session->state == 1)
		return 0;

	if(session->state == 2)
	{
		strcat(buffer, "HTTP/1.1 400\r\n");
		strcat(buffer, "Date: Fri, 10 June 2017 06:07:21 GMT\r\n");
		strcat(buffer, "Content-Type: text/html; charset=UTF-8\r\n");
		write(session->fd, buffer, strlen(buffer));
		return 0;
	}

	strcat(buffer, "HTTP/1.1 200 OK\r\n");
	
	strcat(buffer, "Date: Fri, 10 June 2017 06:07:21 GMT\r\n");
	strcat(buffer, "Content-Type: text/html; charset=UTF-8\r\n");
	strcat(buffer, "\r\n");
		
	read_filedata("html/test.html", &buffer[strlen(buffer)]);

	printf("buffer:\n%s\n", buffer);

	write(session->fd, buffer, strlen(buffer));

	return 0;
}
