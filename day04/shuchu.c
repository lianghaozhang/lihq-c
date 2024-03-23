#include <stdio.h>

int main(void)
{
	char arr[] = {'A', 'B', 'C', 'D', 'E', 'F'};
	int len = sizeof(arr) / sizeof(arr[0]);
	int i, j;
	for(i = 0; i < len; i++)
	{
		for(j = i; j < len; j++)
		{
			printf("%c", arr[j]);
		}
		printf("\n");
	}

	return 0;
}
