CC=gcc
CFLAGS= -o
SRC=ls.c ls_f.c
TARGET=ls

$(TARGET):$(SRC)
	$(CC) $^ $(CFLAGS) $@


%.o:%.c
	$(CC) -c $^ $(CFLAGS) $@

clean:
	rm -rf $(TARGET) *.o
