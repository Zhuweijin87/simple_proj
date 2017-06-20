/*************************
 * 文件处理 
 * ***********************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int file_read(char *filepath, char *out)
{
	FILE	*fp;
	int		fsize;

	fp = fopen(filepath, "r");
	if(fp == NULL)
	{
		fprintf(stderr, "open file fail: %s\n", strerror(errno));
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	
	fsize = ftell(fp);
	
	
	return 0;
}
