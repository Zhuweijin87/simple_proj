#ifndef _CLIENT_SESSION_H
#define _CLIENT_SESSION_H

typedef struct client_session_s
{
	int		fd;
	int		state;
	char	route[65];
	char	method[10];
	char	readbuf[2048];
	char	writebuf[2048];
} ClientSession;

ClientSession *http_create_session(int fd);

void http_destroy_session(ClientSession **session);

#endif

