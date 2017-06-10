#include <stdio.h>
#include <string.h>

int http_read(int c)
{
	int		ret;
	int		len;
	char	buffer[1024] = {'\0'};

	len = read(c, buffer, 1203);
	if(len < 0)
	{
		close(c);
		return -1;
	}
	else if(len == 0)
	{
		printf("client close\n");
		close(c);
	}
	else
	{
		fprintf(stderr, "READ:\n%s\n", buffer);
	}

	return 0;
}

/* 处理GET请求 */
int http_get(int c)
{
	return 0;
}

/* 处理POST请求 */
int http_post(int c)
{
	return 0;
}

