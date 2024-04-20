#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void f(int);

int main(void)
{
	puts("start");
	signal(SIGALRM, f);
	alarm(3);
	pause();
	puts("end");
	exit(0);
}


static void f(int a)
{
	puts("pause()被打断");
}
