#include <stdio.h>

int main(void)
{
	int a = 255;
	printf("(a)H = %#x\n(a)O = %#o\n", a, a);
	int i = printf("1234567\n");
	printf("%d\n", i);
	return 0;
}
