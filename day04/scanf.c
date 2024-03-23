#include <stdio.h>

#define MAXLEN (20)

int main(void)
{
	char str[MAXLEN];
	char* ret;
	printf("input string: ");
	//返回值是输入的字符
	ret = gets(str);
	//scanf("%s", str);
	printf("%s\n", str);
	printf("%s\n", ret);
#if 0
	char* str;
	printf("input string: ");
	scanf("%s", str);
	printf("\n%s\n", str);
	return 0;
#endif
	return 0;
}
