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

	http_parser(session->request, buffer);
	
	if(strcmp(session->request->method, "GET") == 0)
		http_request_get(session);
	else if(strcmp(session->request->method, "POST") == 0)
		http_request_post(session);
	else
		;

	return 0;
}

/* http request数据解析 */
int http_parser(HttpRequest *request, char *recvbuf)
{
	int			offset = 0, charpos = 0;
	char		line[256] = {'\0'};

	request->params = hashtbl_new();

	buffer_get_line(recvbuf, &linepos, line);

	buffer_by_delim(line, ' ', &charpos, request->method);
	buffer_by_delim(line, ' ', &charpos, request->url);
	buffer_by_delim(line, '\r', &charpos, request->version);

	while( buffer_get_line(recvbuf, &linepos, line) != EMPTY_LINE)
	{
		charpos = 0;
		buffer_by_delim_with_ltrim(line, ':', &charpos, key);
		buffer_by_delim_with_ltrim(line, '\0', &charpos, val);
		hash_setstring(request->params, key, val);
	}

		
	return 0;
}

/* 处理GET请求 */
int http_request_get(HttpSession *session)
{
	int		i, offset;

	HttpRequest	*request = &session->request;

		
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

