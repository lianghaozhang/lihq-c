#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	fprintf(stdout, "START!\n");
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid == 0)
	{
		execl("tar", "1", "2", "3", "4", "5", NULL);
		perror("execl()");
	}

	wait(NULL);

	fprintf(stdout, "END!\n");
	exit(0);
}
