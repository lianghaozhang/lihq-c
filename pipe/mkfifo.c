#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int res;
	int fd;
	res = mkfifo("mypipe", 0666);
	if(res)
	{
		perror("mkfifo()");
		exit(1);
	}

	fd = open("mypipe", O_WRONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	write(fd, "this is mkfifo.c\n", 17);
	close(fd);




	exit(0);
}
