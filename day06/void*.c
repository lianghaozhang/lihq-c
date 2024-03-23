#include <stdio.h>

void f(void*);

int main(void)
{
	int i = 99;
	char c = 'a';
	f(&c);
	return 0;
}



void f(void* v)
{
	char* p = (char*)v;
	printf("v --> %c\n", *p);
}
