#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define CPS	20
#define BUFSIZE	CPS

static volatile int loop = 0;

static void alrm_handler(int);

int main(int argc, char** argv)
{
	int fd;
	char buf[BUFSIZE];
	ssize_t size;
	struct itimerval itv;
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
	
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	
	setitimer(ITIMER_REAL, &itv, NULL);	

	while((size = read(fd, buf, BUFSIZE)) > 0)
	{
		while(!loop)
			pause();
		loop = 0;
		write(1, buf, size);
	}
	close(fd);

	exit(0);
}

static void alrm_handler(int i)
{
	loop = 1;
}
