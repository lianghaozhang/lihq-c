CFLAGS+=-pthread
LDFLAGS+=-pthread

all: relayer

relayer: main.o relayer_poll.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf relayer *.o
