/******************************************
 * REQUEST 请求处理
 * ****************************************/
#include <stdio.h>
#include <string.h>
#include "session.h"
#include "util/buffer.h"

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
	int			lineset = 0, chset = 0;
	char		line[256] = {'\0'};
	char		key[33] = {'\0'}, val[256] = {'\0'};

	printf("parser begin\n");
	buffer_get_line(recvbuf, &lineset, line);
	printf("line: %s\n", line);
	buffer_by_delim(line, &chset, ' ', request->method);
	buffer_by_delim(line, &chset, '?', request->url);
	buffer_by_delim(line, &chset, ' ', request->indata);
	buffer_by_delim(line, &chset, '\0', request->version);

	printf("%s,%s,%s\n", request->method, request->url, request->version);
	memset(line, 0, sizeof(line));
	while( buffer_get_line(recvbuf, &lineset, line) != EMPTY_LINE)
	{
		chset = 0;
		memset(key, 0, sizeof(key));
		memset(val, 0, sizeof(val));
		buffer_by_delim(line, &chset, ':', key);
		buffer_by_delim(line, &chset, '\0', val);
		printf("key:%s, val: %s\n", key, val);
		//hash_setstring(request->headers, key, val, 256);
		memset(line, 0, sizeof(line));
	}
		
	request->params = hashtbl_new();

	return 0;
}

/* 处理GET请求 */
int http_request_get(HttpSession *session)
{
	int		i, offset;

	HttpRequest	*request = session->request;

		
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

