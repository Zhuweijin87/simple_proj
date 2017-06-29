/**************************
 * 简单的登录测试
 * ***********************/

#include "session.h"
#include <stdio.h>


int myapp_login(HttpSession *session)
{
	char	username[20] = {'\0'};
	char	password[20] = {'\0'};

	hash_getstring(session->request->params, "username", username, 20);
	hash_getstring(session->request->params, "password", password, 20);

	if(strcmp(username, "admin") == 0 && strcmp(password, "111111") == 0)
	{
		fprintf(stderr, "登录成功\n");
	}
	else
	{
		fprintf(stderr, "登录失败\n");
	}

	return 0;
}
