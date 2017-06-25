/* 数据流处理 */
#include <stdio.h>
#include <string.h>
#include "buffer.h"

int buffer_get_line(char *buffer, int *offset, char *line)
{
	int i = *offset;
	for( ; buffer[i] != '\n'; i++)
	{
		if(buffer[i] == '\r')
			continue;
		if(buffer[i] == '\0')
			break;
		*line++ = buffer[i];
	}

	*offset = i;

	if(strlen(buffer) == 0)
		return EMPTY_LINE;
	return OK;
}

int buffer_by_delim(char *line, int *offset, char ch, char *out)
{
	int  i = *offset;
	for(; line[i] != ch; i++)
	{
		if(line[i] == '\0')
			break;
		*out++ = line[i];
	}
	*offset = i;
	return OK;
}

int buffer_by_delim_with_ltrim(char *line, int *offset, char ch, char *out)
{
	int	start = 0;
	int i = *offset;
	for(; line[i] != ch; i++)
	{
		if(start == 0 && line[i] != 0x20)
			start = 1;
		*out++ = line[i];
	}
	*offset = i;
	return OK;
}


