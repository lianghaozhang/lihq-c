#include <stdio.h>
#include "project.h"

int i = 999;

int main(void)
{
	printf("1) this is main.c de i ---> %d\n", i);
	call_f();
	return 0;
}
