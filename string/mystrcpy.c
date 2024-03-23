#include <stdio.h>
#include <stdlib.h>

char* f(char* , const char* );

int main(void)
{
	char str1[] = "hello world";
	char str2[128];
	char* ans = f(str2, str1);
	puts(ans);
	exit(0);
}



char* f(char* dest, const char* src)
{
	char* ret = dest;
	if(dest != NULL && src != NULL)
		while((*dest++ = *src++) != '\0');
	
	return ret;
}
