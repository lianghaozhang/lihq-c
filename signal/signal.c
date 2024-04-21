#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void f(int);

int main(void)
{
	int i;
	signal(SIGINT, f);
	//signal(SIGINT, SIG_IGN);
	for(i = 0; i < 10; i++)
	{
		fprintf(stdout, "*");
		fflush(stdout);
		sleep(1);
	}
	
	fprintf(stdout, "\n");

	exit(0);
}


void f(int i)
{
	FILE* fp = NULL;
	fp = fopen("lloogg", "w|a");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	fprintf(fp, "法克鱿啊\n");
	fclose(fp);
}
