#include <string.h>
#include <stdlib.h>

BufferHandle *BufferHandle_New(const char *buffer)
{
	BufferHandle *handle = malloc(sizeof(BufferHandle));
	handle->offset = 0;
	handle->buffer = strdup(buffer);

	return handle;
} 

int get_buffer_by_delim(BufferHandle *handle, char ch, char *out)
{
	int  i = handle->offset;
	for(; handle->buffer[i] != ch; i++)
	{
		*out++ = handle->buffer[i];
	}
	handle->offset = i;
	return 0;
}

