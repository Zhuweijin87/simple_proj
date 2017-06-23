#include <stdio.h>
#include <time.h>
#include <string.h>

int get_datetime(char *gmtTime)
{
	char		temp[50] = {'\0'};
	time_t		tms;
	struct tm  *ptime;
	
	time(&tms);
	ptime = gmtime(&tms);
	strftime(temp, sizeof(temp), "%a, %d %b %Y %H:%M:%S GMT", ptime);
	strcpy(gmtTime, temp);
	
	return 0;
}

int read_filedata(char *fileName, char *buffer)
{
	FILE	*fp = NULL;

	fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		fprintf(stderr, "fail to open %s\n", fileName);
		return -1;
	}

	fseek(fp, 0, SEEK_END);

	int len = ftell(fp);
	
	fseek(fp, 0, SEEK_SET);

	fread(buffer, 1, len, fp);

	return 0;
}

int read_by_delim(char *buffer, char ch, int *offset, char *out)
{
	int i = *offset;
	for( ; buffer[i] != ch && buffer[i] != '\0'; i++)
	{
		*out++ = buffer[i];
	}
	*offset = i+1;
	return 0;
}

int getpos_by_delim(char *buffer, char ch)
{
	int pos = 0;
	for( ; buffer[pos] != ch && buffer[pos] != '\0'; pos++)
	{
		;
	}

	return pos;
}

int get_buffer_line(char *buffer, char *line)
{
	int	pos;
	
}

