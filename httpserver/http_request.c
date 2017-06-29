/******************************************
 *  * REQUEST 请求处理
 *   * ****************************************/
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

	//printf("%s\n", buffer);

	http_request_parser(session->request, buffer);
	
	if(strcmp(session->request->method, "GET") == 0)
		http_request_get(session);
	else if(strcmp(session->request->method, "POST") == 0)
		http_request_post(session);
	else
		;

	return 0;
}

/* http request数据解析 */
int http_request_parser(HttpRequest *request, char *recvbuf)
{
	int			lineset = 0, chset = 0;
	char		line[256] = {'\0'};
	char		indata[256] = {'\0'};
	char		reqData[256] = {'\0'};
	char		key[33] = {'\0'}, val[256] = {'\0'};

	buffer_get_line(recvbuf, &lineset, line);

	buffer_split_by(line, &chset, ' ', request->method);
	buffer_split_by(line, &chset, ' ', indata);
	buffer_split_by(line, &chset, '\0', request->version);

	request->headers = hashtbl_new();
	memset(line, 0, sizeof(line));
	while( buffer_get_line(recvbuf, &lineset, line) != EMPTY_LINE)
	{
		printf("%s\n", line);
		memset(line, 0, sizeof(line));
	}
		
	request->params = hashtbl_new();
	char  temp[100] = {'\0'};
	int i=0, j=0, tag = 0;
	while(indata[i] != '\0')
	{
		if(indata[i] == '?')
		{
			strncpy(request->tempDir, &indata[j], i-j); j = i+1; tag = 1;
		}
		if(indata[i] == '#')
		{
			strncpy(reqData, &indata[j], i-j); j = i+1; tag = 2;
		}
		++i;
	}
	if(tag == 0)
		strncpy(request->tempDir, &indata[j], i-j);
	if(tag == 1)
		strncpy(reqData, &indata[j], i-j);
	if(tag == 2)
		strncpy(request->href, &indata[j], i-j);

	printf("Method: %s, tempDir: %s, version:%s\n", request->method, request->tempDir, request->version);
	if(strcmp(request->method, "POST") == 0 )
	{
		memset(line, 0, sizeof(line));
		buffer_get_line(recvbuf, &lineset, line);
		http_params_parser(request->params, line);
	}
	else
	{
		http_params_parser(request->params, reqData);
	}

	return 0;
}

int http_params_parser(hashtbl_t *hashtbl, char *params)
{
	int i=0, j=0;
	char	temp[256] = {'\0'};
	char key[33] = {'\0'}, val[256] = {'\0'};
	if(strlen(params) == 0)
		return 0;
	//printf("ReqData: %s\n", params);
	while(params[i] != '\0')
	{
		if(params[i] == '&')
		{
			memset(temp, 0, sizeof(temp));
			strncpy(temp, &params[j], i-j); j = i+1;
			memset(key, 0, sizeof(key));
        	memset(val, 0, sizeof(val));
			sscanf(temp, "%[^=]=%s", key, val);
			printf("Key:%s\tValue:%s\n", key, val);
			hash_setstring(hashtbl, key, val);
		}
		++i;
	}

	strncpy(temp, &params[j], i-j); j = i+1;
	memset(key, 0, sizeof(key));
	memset(val, 0, sizeof(val));
	sscanf(temp, "%[^=]=%s", key, val);
	printf("Key:%s\tValue:%s\n", key, val);
	hash_setstring(hashtbl, key, val);
	
	return 0;
}

/* 处理GET请求 */
int http_request_get(HttpSession *session)
{
	int		i, offset;
	
	if(strcmp(session->request->tempDir, "/favicon.ico") == 0)
	{
		session->state = 2;
	}

	return 0;
}

/* 处理POST请求 */
int http_request_post(HttpSession *session)
{
	if(strcmp(session->request->tempDir, "/favicon.ico") == 0)
    {
        session->state = 2;
    }

	return 0;
}

