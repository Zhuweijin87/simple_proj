#include "session.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HttpSession *HttpSession_New(int clientfd)
{
	HttpSession *session = malloc(sizeof(HttpSession));
	session->fd = clientfd;
	session->state = 0;

	session->request = calloc(1, sizeof(HttpRequest));
	session->response = calloc(1, sizeof(HttpResponse));

	return session;
}

void HttpSession_Destroy(HttpSession **session)
{
	HttpSession *http = *session;
	close(http->fd);
	free(http->request);
	free(http->response);
	free(http);
	*session = NULL;
}
