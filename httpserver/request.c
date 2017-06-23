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

	printf("Request:\n%s\n", buffer);

	request = &session->request;
	offset = 0;
	read_by_delim(buffer, ' ', &offset, request->method);	
	read_by_delim(buffer, ' ', &offset, request->url);
	read_by_delim(buffer, '\r', &offset, request->version);

	printf("http: %s,%s,%s\n", request->method, request->url, request->version);	
	if(strncmp(request->method, "GET", 3) == 0)
		http_request_get(session);
	else if(strncmp(request->method, "POST", 4) == 0)
		http_request_post(session);
	
	return 0;
}

/* http request数据解析 */
int http_request_parser(HttpRequest *request, char *buffer)
{
	int		offset = 0;
	
	request->params = hashtbl_new();

	read_by_delim(buffer, ' ', &offset, request->method);
	read_by_delim(buffer, ' ', &offset, request->url);
	read_by_delim(buffer, '\r', &offset, request->version);
	
	
}

/* 处理GET请求 */
int http_request_get(HttpSession *session)
{
	int		i, offset;
	HttpRequest	*request = &session->request;

	offset = 0;
	if(getpos_by_delim(request->url, "?") > 0)
		read_by_delim(request->url, '?', &offset, request->vdir);
	
		
	if(strcmp(request->url, "/favicon.ico") == 0)
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

