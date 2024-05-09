#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE	1024

int main(void)
{
	int res;
	pid_t pid;
	int fd;
	char buf[BUFSIZE];
	res = mkfifo("mypipe_fork", 0666);
	if(res)
	{
		perror("mkfifo()");
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
		fd = open("mypipe_fork", O_WRONLY);
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
		fd = open("mypipe_fork", O_RDONLY);
		if(fd < 0)
		{
			perror("open()");
			exit(1);
		}

		int len = read(fd, buf, BUFSIZE);
		write(1, buf, len);
		close(fd);
		exit(0);
	}

	exit(0);
}
