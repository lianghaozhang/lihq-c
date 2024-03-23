#if 0
	交换二维数组的行和列
#endif

#define M	3
#define N	4

#include <stdio.h>

int main(void)
{
	int arr[M][N] = {
						1, 2, 3, 4, 
						5, 6, 7, 8, 
						9, 10, 11, 12
					};
	int temp[N][M];
	int i, j;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
		{
			temp[j][i] = arr[i][j];
		}
	}

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			printf("%d\t", temp[i][j]);
		}
		printf("\n");
	}
	return 0;
}
