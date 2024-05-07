all: mypipe

mypipe: main.o pipe.o
	gcc $^ -o $@

clean:
	rm -rf *.o mypipe
