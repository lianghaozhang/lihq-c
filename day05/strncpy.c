#include <stdio.h>
#include <string.h>

#define STRLEN	5

static void printarr(char [], int);

int main(void)
{
	char str[STRLEN] = "a";
	#if 0
		strncpy(目标字符串，源字符串，源字符串中最大的复制长度);函数相当于字符串的复制
		
	#endif
	strncpy(str, "12345678", STRLEN - 1);
	//printf("%s\n", str);
	//puts(str);
	printarr(str, STRLEN);
	return 0;
}


static void printarr(char arr[], int len)
{
	int i;
	for(i = 0; i < len; i++)
	{
		printf("%d ", (int)arr[i]);
	}
	printf("\n");
}
