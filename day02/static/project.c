#include <stdio.h>

static int i = 111;

static void f(void)
{
	printf("3) this is project.c de i ---> %d\n", i);	
}

void call_f(void)
{
	printf("2) i am call_f()\n");
	f();
}

