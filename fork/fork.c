#include <stdio.h>
#include <stdlib.h>

#define LEFT	1
#define RIGTH	100

int main(void)
{
	int i, j, flag;
	for(i = LEFT; i <= RIGTH; i++)
	{
		pid_t pid = fork();
		if(pid < 0)
		{
			exit(0);
		}

		if(!pid)
		{
			flag = 1;
			for(j = 2; j < i; j++)
			{
				if(i % j == 0)
				{
					flag = 0;
					break;
				}
			}	
		
			if(flag)
			{
				printf("%d is primer\n", i);
			}
			sleep(1000); //子进程状态为S
			exit(0);
		}
	}
	//sleep(1000); //子进程状态为Z
	exit(0);
}
