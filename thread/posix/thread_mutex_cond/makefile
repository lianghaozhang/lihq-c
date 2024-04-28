CC=gcc
CFLAGS+=-pthread
LDFLAGS+=-pthread

all: tmc

tmc: tmc.o main.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)


clean:
	rm -rf *.o tmc
