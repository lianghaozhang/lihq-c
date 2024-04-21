#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd;
	FILE* fp;
	fd = open("rrrrrrrrrrrrr", O_WRONLY | O_CREAT);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}
	
	dup2(fd, 1);
	if(fd != 1)
		close(fd);

	fp = fopen("rrrrrrrrrrrrr", "r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	puts("HELLO WORLD!");	

	if(fp != stdout)
		fclose(fp);
	
	exit(0);
}
