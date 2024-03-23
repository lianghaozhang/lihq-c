#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRINGLEN	32

int main(void)
{
	//strncpy的用法
	char str[STRINGLEN] = "hello";
	puts(str);	
	strncpy(str, "Hello World", STRINGLEN - 1);

#if 0
	//strcpy用法	
	puts(str);
	strcpy(str, "HELLO");
	puts(str);
#endif




	exit(0);
}
