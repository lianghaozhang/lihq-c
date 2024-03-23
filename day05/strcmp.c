#include <stdio.h>
#include <string.h>

#define PASSWORD	"abcd123"

int main(void)
{
	char str[32];
	while(1)
	{
		printf("请输入密码：");
		scanf("%s", str);
		if(!strcmp(str, PASSWORD))	
		{
			printf("密码正确！\n");
			break;	
		}
		else
		{
			printf("密码错误请重新输入！\n**************************\n");	
		}
	}

	return 0;
}
