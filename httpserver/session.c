#include "session.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ClientSession *http_create_session(int clientfd)
{
	ClientSession *session = malloc(sizeof(ClientSession));
	session->fd = clientfd;
	session->state = 0;
	return session;
}

void http_close_session(ClientSession **session)
{
	close((*session)->fd);
	free(*session);
	*session = NULL;
}
