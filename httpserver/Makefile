CC=gcc
CFLAG=-g

TARGET=httpserver

OBJ=httpserver.o request.o response.o

all:$(TARGET)

%.o:%.c
	$(CC) $(CFLAG) -c $<

httpserver:$(OBJ)
	$(CC) $(CFLAG) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
