#include <stdio.h>
#include <stdlib.h>


static void startDaemon(void);
static void daemonWorking(void);


int main(void)
{

	startDaemon();

	daemonWorking();

	exit(0);
}


static void startDaemon(void)
{
	pid_t pid;
	pid = fork();
	int fd;
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid > 0)
		exit(0);

	fd = open("/dev/null", O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if(fd > 2)
		close(fd);

	setsid();
	chdir("/");
}


static void daemonWorking(void)
{
	FILE* fp = NULL;
	fp = fopen("oooooo", "w");
	if(fd == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	
	while(1)
	{
		fprintf(fp, "%d\n", i++);
		sleep(5);
	}

	fclose(fp);
}
