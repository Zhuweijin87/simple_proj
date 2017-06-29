#include "hashtbl.h"
#include <stdio.h>
#include <string.h>
#include "buffer.h"

int hashtable_test()
{
	hashtbl_t	*hashtbl;

	hashtbl = hashtbl_new();
	
	hash_setstring(hashtbl, "Name", "Zhangshan");
	hash_setstring(hashtbl, "Value", "#33454354");

	char	 val[100] = {'\0'};
	hash_getstring(hashtbl, "Name", val, 100);
	printf("val:%s\n", val);
	
	memset(val, 0, sizeof(val));
	hash_getstring(hashtbl, "Value", val, 100);
	printf("val:%s\n", val);
	
	return 0;
}

int buffer_test()
{
	int	 lineset = 0;
	char s[] = 	"GET /?a=10&b=xxverfghf&sex=gender#name@r42 HTTP/1.1\r\n"
			   	"Host: 192.168.1.46:8001\r\n"
				"Connection: keep-alive\r\n"
				"Cache-Control: max-age=0\r\n"
				"Upgrade-Insecure-Requests: 1\r\n"
				"User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) "
							"Chrome/58.0.3029.110 Safari/537.36\r\n"
				"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
				"Accept-Encoding: gzip, deflate, sdch\r\n"
				"Accept-Language: zh-CN,zh;q=0.8\r\n"
				"\r\n";

	char line[200] = {'\0'};

	buffer_get_line(s, &lineset, line);
	
	int i=0, j=0, tag=0;
	char	temp[200] = {'\0'};
	char  	vdir[100]={'\0'}, params[200] = {'\0'}, href[100] = {'\0'};
	char	method[5] = {'\0'}, version[15] = {'\0'};
	int		v1=0;
	sscanf(line, "%s %s %s", method, temp, version);
	int len = strlen(temp);
	for(i=0; i<len; i++)
	{
		if(temp[i] == '?')
		{
			strncpy(vdir, &temp[j], i-j); j = i+1; v1 = 1;
		}
		if(temp[i] == '#')
		{
			strncpy(params, &temp[j], i-j); j = i+1; v1 = 2;
		}
	}		
	
	if(v1 == 0)
		strncpy(vdir, &temp[j], i-j);
	if(v1 == 1)
		strncpy(params, &temp[j], i-j);
	if(v1 == 2)
		strncpy(href, &temp[j], i-j);

	printf("method: %s, version:%s\n", method, version);
	printf("vdir:%s, params:%s, href:%s\n", vdir, params, href);
	memset(line, 0, sizeof(line));

	while( buffer_get_line(s, &lineset, line) != EMPTY_LINE )
	{
		printf("line: %s\n", line);
		memset(line, 0, sizeof(line));
	}
	
	return 0;
}

int buffer_test2()
{
	char	s[] = "a=2&b=23.45&c=werer";

	int set = 0;
	char out[20] = {'\0'};

	int n;
	n = buffer_split_end_by(s, &set, '&', out);
	printf("%d, %s\n", n, out);
	memset(out, 0, sizeof(out));
	n = buffer_split_end_by(s, &set, '&', out);
    printf("%d, %s\n", n, out);
	memset(out, 0, sizeof(out));
    n = buffer_split_end_by(s, &set, '&', out);
    printf("%d, %s\n", n, out);

/*	
	while( buffer_split_by(s, &set, '&', out) != END_OF_LINE)
	{
		printf("out: %s\n", out);
		memset(out, 0, sizeof(out));
	}
*/

	char  b[] = "/?ewrwe&ds&s23#";
	set = 0;
	buffer_char_at(b, '?', &set);
	printf("set: %d\n", set);	
	buffer_char_at(b, '&', &set);
	printf("set: %d\n", set);
	buffer_char_at(b, '&', &set);
	printf("set: %d\n", set);
	buffer_char_at(b, '#', &set);
	printf("set: %d\n", set);
	return 0;
}

int main()
{
	hashtable_test();
	buffer_test();

	buffer_test2();
	return 0;
}
