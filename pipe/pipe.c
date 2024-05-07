#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	struct fd_pair pfd;
	pid_t pid;
	pfd = pipe();
	if(pfd < 0)
	{
		perror("pipe()");
		exit(1);
	}
	
	long p_read = pfd.fd[0];
	long p_write = pfd.fd[1];

	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid > 0) //parent write
	{
		
	}
	else
	{
	
	}

	exit(0);
}
