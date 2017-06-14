#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int http_write(int c)
{
	int		ret;
	char	buffer[1024] = {'\0'};

	//strcat(buffer, "HTTP/1.1 200 OK\r\n");
	strcat(buffer, "HTTP/1.1 400\r\n");
	/*
	strcat(buffer, "Date: Fri, 10 June 2017 06:07:21 GMT\r\n");
	strcat(buffer, "Content-Type: text/html; charset=UTF-8\r\n");
	strcat(buffer, "\r\n");
	strcat(buffer, "<html>\r\n");
	strcat(buffer, "<head>Web Test</head>\r\n");
	strcat(buffer, "<body>\r\n");
	strcat(buffer, "<h1>HelloWorld</h1>\r\n");
	strcat(buffer, "</body>\r\n");
	strcat(buffer, "</html>\r\n");
	*/
	write(c, buffer, strlen(buffer));

	return 0;
}
