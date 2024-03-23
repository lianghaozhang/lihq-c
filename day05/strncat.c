#include <stdio.h>
#include <string.h>

#define MAXLEN	8

int main(void)
{
	char str[MAXLEN] = "12345";
	strncat(str, "678910", 2);
	puts(str);
	return 0;
}
