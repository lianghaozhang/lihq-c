#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid == 0)
	{
		fprintf(stdout, "[%d]:child is working...\n", getpid());
		sleep(1000);

	}
	else
	{
		fprintf(stdout, "[%d]:parent is working...\n", getpid());
	}

	exit(0);
}
