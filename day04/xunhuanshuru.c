#include <stdio.h>

int main(void)
{
	int res, i;
	int sum = 0;
	while(1)
	{
		printf("input number: ");	
		res = scanf("%d", &i);
		if(res != 1) break;
		sum += i;	
	}
	
	printf("sum = %d\n", sum);
	return 0;
}
