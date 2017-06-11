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

	if(strncmp(buffer, "GET", 3) == 0)
	{
		http_get(c, buffer);
	}

	if(strncmp(buffer, "POST", 4) == 0)
	{
		http_post(c, buffer);
	}

	return 0;
}

/* 处理GET请求 */
int http_get(int c, char *buffer)
{
	char	getdata[256] = {'\0'};
	char	*p = buffer;
	int		tag = 0, i=0;	
	for( ; *p != '\n'; *p++)
	{
		if(*p == '/')
		{
			tag = 1;
			continue;
		}
	
		if(tag == 1 && *p == ' ')
		{
			tag = 0;
			break;
		}

		if(tag == 1)
			getdata[i++] = *p;		
	}

	printf("getdata: %s\n", getdata);
	
	if(getdata[0] == '?')
	{		
		;
	}
	else
	{
		;	
	}

	return 0;
}

/* 处理POST请求 */
int http_post(int c, char *buffer)
{
	return 0;
}

