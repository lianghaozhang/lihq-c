#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
	int i;
	signal(SIGINT, SIG_IGN);
	for(i = 0; i < 10; i++)
	{
		fprintf(stdout, "*");
		fflush(stdout);
		sleep(1);
	}
	
	fprintf(stdout, "\n");


	exit(0);
}
