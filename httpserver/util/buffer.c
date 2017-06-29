/* 数据流处理 */
#include <stdio.h>
#include <string.h>
#include "buffer.h"

int buffer_get_line(char *buffer, int *offset, char *line)
{
	int j = 0;
	int i = *offset;
	for( ; buffer[i] != '\n'; i++)
	{
		if(buffer[i] == '\r')
			continue;
		if(buffer[i] == '\0')
			break;
		line[j++] = buffer[i];
	}

	*offset = i+1;

	if(j == 0)
		return EMPTY_LINE;
	return OK;
}

int buffer_by_delim(char *line, int *offset, char ch, char *out)
{
	int  i = *offset;
	for(; line[i] != ch; i++)
	{
		if(line[i] == '\0' || line[i] == ' ')
			break;
		*out++ = line[i];
	}
	*offset = i+1;
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

int buffer_split_by(const char *line, int *offset, char ch, char *out)
{
	int i = *offset;
	char *p = (char *)line + i;

	for(; *p != ch; i++)
	{
		if(*p == '\0')
			break;
		*out++ = *p++;
	}

	if(i == strlen(line))
		return END_OF_LINE;

	*offset = i+1;
	return i+1;
}

int buffer_split_end_by(const char *line, int *set, char ch, char *out)
{
	int  i = *set, j = 0;
	char *p = (char *)line + i;
	while(*p != '\0')
	{
		if(*p == ch)
		{
			*set = i + j;
			strncpy(out, (char *)line + i, j);
			return i;
		}
		++j;
		++(*p);
	}
	return 0;
}

int buffer_char_at(const char *line, char ch, int *offset)
{
	int 	len = strlen(line);
	char	*p = (char *)line + (*offset);
	for(; *p++ != ch && (*offset) <= len; (*offset)++) {}
	++(*offset);
	return 0;
}

