/******************************************
 * REQUEST 请求处理
 * ****************************************/
#include <stdio.h>
#include <string.h>
#include "session.h"

int http_request(HttpSession *session)
{
	int		ret;
	int		len, offset;
	char	buffer[1025] = {'\0'};
	HttpRequest  *request = NULL;

	len = read(session->fd, buffer, 1024);
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

#ifdef DEBUG
	printf("Request:\n%s\n", buffer);
#endif

	request = &session->request;
	offset = 0;
	read_by_delim(buffer, ' ', &offset, request->method);	
	read_by_delim(buffer, ' ', &offset, request->params);
	read_by_delim(buffer, '\r', &offset, request->version);

	printf("http: %s,%s,%s\n", request->method, request->params, request->version);	
	if(strncmp(request->method, "GET", 3) == 0)
		http_request_get(session);
	else if(strncmp(request->method, "POST", 4) == 0)
		http_request_post(session);
	
	return 0;
}

/* 处理GET请求 */
int http_request_get(HttpSession *session)
{
	int		i;
	HttpRequest	*request = &session->request;

	if(request->params[0] == '/')
	{
		printf("params: %s\n", request->params);	
	}
	else
	{
		printf("");
	}

	if(strcmp(session->request.params, "/favicon.ico") == 0)
	{
		session->state = 2;
	}

	return 0;
}

/* 处理POST请求 */
int http_request_post(HttpSession *session)
{
	return 0;
}

