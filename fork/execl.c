#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("start\n");
	pid_t pid = fork();	
	if(pid < 0) exit(0);
	if(pid == 0)
	{
		execl("./hello", NULL);
	}
	//wait(NULL);
	printf("end\n");
	exit(0);
}
