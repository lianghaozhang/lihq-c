#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE	1024

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stdout, "Usage...\n");
		exit(1);
	}
	
	int fd, len;
	char buf[BUFSIZE];
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	while((len = read(fd, buf, BUFSIZE)) > 0)
		write(1, buf, len);
	
	close(fd);

//	sleep(10000);
	exit(0);
}
