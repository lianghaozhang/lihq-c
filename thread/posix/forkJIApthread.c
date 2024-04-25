#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

static void alrm_handler(int i)
{
	fprintf(stdout, "到点了\n");
}

typedef void (*sighandler_t)(int);

int main(void)
{
	pid_t pid;
	pthread_t tid;
	struct itimerval itv;
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	
	signal(SIGALRM, alrm_handler);
	if(setitimer(ITIMER_REAL, &itv, NULL))
	{
		perror("setitimer()");
		exit(1);
	}
	
	pid = fork();
	while(1)
	{
		if(pid > 0)
		{
			fprintf(stdout, "This is paren fork\n");
		
		}

		if(pid == 0)
		{
			fprintf(stdout, "This is child fork\n");
		}

	}

	exit(0);
}
