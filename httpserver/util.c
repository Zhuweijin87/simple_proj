#include <stdio.h>
#include <time.h>

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

	fseek(fp, 0, SEEK_SET);

	int len = ftell(fp);
	
	fread(fp, buffer, len);

	return 0;
}

