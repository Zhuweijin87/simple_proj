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
	char s[]= "This is Test View\r\nCache-Type: hekliicldf\r\nLength: 2345\r\nBuffer-Data: xhtml-text/*.gif,*.jpg\r\n\n";
	char line[100] = {'\0'};

	while( buffer_get_line(s, &lineset, line) != EMPTY_LINE )
	{
		printf("line: %s\n", line);
		memset(line, 0, sizeof(line));
	}
	
	int cset = 0;
	char val[50] = {'\0'};
	
	buffer_by_delim(s, &cset, ' ', val);
	printf("val: %s\n", val);
	memset(val, 0, sizeof(val));
	buffer_by_delim(s, &cset, ' ', val);
	printf("val: %s\n", val);

	cset = 0;
	memset(val, 0, sizeof(val));
	buffer_by_delim(s, &cset, ':', val);
	printf("val: %s\n", val);
	return 0;
}

int main()
{
	hashtable_test();
	buffer_test();
	return 0;
}
