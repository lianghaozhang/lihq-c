# if 0
	在八位二进制数中取出strat-end位
#endif

#include <stdio.h>
#include <math.h>

void f(int, int, int);

int main(void)
{
	//int num, s, e;
	//scanf("请输入一个数：%d", &num);
	//scanf("\n请输入开始位置：%d", &s);
	//scanf("\n请输入结束位置：%d", &e);
	f(20, 2, 6);
	return 0;
}



void f(int val, int start, int end)
{
	int num = val;
	int arr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int i = 7;
	int b = num % 2;
	arr[i] = b;
	num /= 2;
	while(num)
	{
		i--;
		b = num % 2;
		arr[i] = b;
		num /= 2;
	}
	
	printf("%d的二进制表示：\t", val);
	for(i = 0; i < 8; i++)
	{
		printf("%d", arr[i]);
	}


	printf("\n%d的%d到%d位数据为：\t", val, start, end);	
	for(i = start; i <= end; i++)
	{
		if(arr[i] & 1) printf("1");
		else printf("0");
	}
	printf("\n");
}
