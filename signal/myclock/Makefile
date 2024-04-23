all: myclock

myclock: main.o myclock.o
	gcc $^ -o $@

clean:
	rm -rf myclock *.o
