#include "session.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HttpSession *HttpSession_New(int clientfd)
{
	HttpSession *session = malloc(sizeof(HttpSession));
	session->fd = clientfd;
	session->state = 0;

	memset(&session->request, 0, sizeof(HttpRequest));
	memset(&session->response, 0, sizeof(HttpResponse));

	return session;
}

void HttpSession_Destroy(HttpSession **session)
{
	close((*session)->fd);
	free(*session);
	*session = NULL;
}
