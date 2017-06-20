#ifndef _CLIENT_SESSION_H
#define _CLIENT_SESSION_H

typedef struct http_request_s
{
    char    method[7];
    char    params[1024];
    char    version[10];
} HttpRequest;

typedef struct http_response_s
{
	char	respcode[5];
	char	date[50];
    char    html[2048];
} HttpResponse;

typedef struct http_session_s
{
	int				fd;
	int				state;
	HttpRequest		request;
	HttpResponse	response;
} HttpSession;

HttpSession *HttpSession_New(int fd);

void HttpSession_Destroy(HttpSession **session);

#endif

