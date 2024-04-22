#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define CPS	20
#define BUFSIZE	CPS
#define BUFMAX	100

static volatile int token = 0;

static void alrm_handler(int);

int main(int argc, char** argv)
{
	int fd;
	char buf[BUFSIZE];
	ssize_t size;
	if(argc < 2)
	{
		fprintf(stdout, "Usage...\n");
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	signal(SIGALRM, alrm_handler);
	alarm(1);

	while((size = read(fd, buf, BUFSIZE)) > 0)
	{
		while(token <= 0)
			pause();
		token--;
		write(1, buf, size);
	}
	close(fd);

	exit(0);
}


static void alrm_handler(int i)
{
	alarm(1);
	token++;
	if(token > BUFMAX)
		token = BUFMAX;
}	
