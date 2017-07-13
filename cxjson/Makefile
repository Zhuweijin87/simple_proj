CC=gcc -m32 -g
CFLAG=
INC_HOME=

TARGET=libcJson.a test

OBJ_FILE=cJSON.o cxJson.o

all:$(TARGET)

libcJson.a:$(OBJ_FILE)
	ar -rv $@ $(OBJ_FILE)

test:test.o cJSON.o cxJson.o
	$(CC) -o $@ test.o cJSON.o cxJson.o -lm

clean:
	rm -f $(TARGET) *.o

