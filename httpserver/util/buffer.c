/* 数据流处理 */
#include <stdio.h>
#include <string.h>

void buffer_init(buffer_t *buffer, char *data)
{
	buffer->offset = 0;
	buffer->data = data;
}

void buffer_reset(buffer_t *buffer)
{
	buffer->offset = 0;
}

int buffer_get_line(buffer_t *buffer, char *line)
{
	char *ptr = buffer->data + buffer->offset;
	while(*ptr != '\n')
	{
		if(*ptr == '\r')
			*ptr++;
		if(*ptr == '\0' || *ptr == '\n')
			break;
		*line++ = *ptr++;
	}
	return 0;
}

int buffer_by_delim(char *line, char ch)
{

}

