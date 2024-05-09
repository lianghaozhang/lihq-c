#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE	1024

int main(int agrc, char** argv)
{
	/*
	if(argc < 0)
	{
		fprintf(stdout, "Usage...\n");
		exit(1);
	}
	*/

	int res;
	pid_t pid;
	int fd;
	char buf[BUFSIZE];
	res = mkfifo("mypipe_fork_execl", 0666);
	if(res)
	{
		perror("mkfifo");
		exit(1);
	}
	
	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	
	if(pid > 0)	//p w
	{
		fd = open("mypipe_fork_execl", O_WRONLY);
		if(fd < 0)
		{
			perror("open()");
			exit(1);
		}

		char* str = "Hello World!\n";
		write(fd, str, strlen(str));
		close(fd);
		wait(NULL);
	}
	else	//c r
	{
		execl("./mycat", "mycat", "mypipe_fork_execl", NULL);
		perror("execl()");
		exit(1);
	}

	exit(0);
}
