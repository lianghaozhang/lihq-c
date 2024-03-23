#include <stdio.h>

int main(void)
{
	int i, j, flag = 1;
	for(i = 1; i <= 1000; i++)
	{
		flag = 1;
		for(j = 2; j < i; j++)
		{
			if((i % j) == 0)
			{
				flag = 0;
				break;
			}
		}
		
		if(flag) printf("%d\n", i);
	}
	
	return 0;
}
