#ifndef _HTTP_H
#define _HTTP_H

typedef struct http_request_s
{
	char	method[7];
	char	params[1024];
	char	version[10];
} HttpRequest;

typedef struct http_response_s
{
	char	html[2048];	
} HttpResponse;

#endif

