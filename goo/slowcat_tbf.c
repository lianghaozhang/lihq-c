#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CPS	20
#define BURST	1000
#define BUFSIZE	CPS

static volatile int loop = 1;
static int token = 0;

static void alrm_handler(int);
static void module_destroy(void);

typedef void (*sighandler_t)(int);

static sighandler_t alrm_handler_old;

int main(int argc, char** argv)
{
	int fd;
	char buf[BUFSIZE];
	ssize_t len;

	if(argc < 2)
	{
		fprintf(stdout, "Usage...\n");
		exit(1);
	}

	atexit(module_destroy);

	alrm_handler_old = signal(SIGALRM, alrm_handler);
	alarm(1);

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	while(1)
	{
		len = read(fd, buf, BUFSIZE);
		if(len <= 0)
			break;

		write(1, buf, len);

		while(token <= 0)
			pause();
		token -= BURST;	
	}

	exit(0);
}


static void alrm_handler(int s)
{
	token += BURST;
	if(token > BURST)
		token = BURST;

	alarm(1);
}


static void module_destroy(void)
{
	signal(SIGALRM, alrm_handler_old);
}




