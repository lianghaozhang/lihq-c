#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
	puts("START!");
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid == 0)
	{
		fprintf(stdout, "[%d]:this is child working...\n", getpid());
	}
	else
	{
		fprintf(stdout, "[%d]:this is parent working...\n", getpid());
	}

	puts("END!");

	exit(0);
}
