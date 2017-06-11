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

