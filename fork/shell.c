#include <stdio.h>
#include <stdlib.h>

#define MAXCMDSIZE	1024

int main(void)
{
	while(1)
	{
		fprintf(stdout, "aniu@aniu ~$ ");
		char cmd[MAXCMDSIZE];
		fgets(cmd, MAXCMDSIZE, stdin);
		fprintf(stdout, "%s", cmd);
	}


	exit(0);
}
