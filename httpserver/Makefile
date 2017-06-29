CC=gcc
CFLAG=-g

TARGET=httpserver

OBJ=http_server.o http_request.o http_response.o session.o util/util.o util/hashtbl.o util/buffer.o

all:$(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $< -o $@

httpserver:$(OBJ)
	$(CC) $(CFLAG) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
