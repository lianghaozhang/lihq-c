#include <stdio.h>
#include <stdlib.h>

#include "myclock.h"

static void f1(char*);
static void f2(char*);
static void f3(char*);

int main(void)
{
	addClock(10, "尿尿",f1);
	addClock(20, "吃饭",f3);
	addClock(15, "喝水",f2);

	showJob();
	while(1);
	exit(0);
}


static void f1(char* s)
{
	fprintf(stdout, "%s", s);
	fflush(stdout);
}

static void f2(char* s)
{
	fprintf(stdout, "%s", s);
	fflush(stdout);
}

static void f3(char* s)
{
	fprintf(stdout, "%s", s);
	fflush(stdout);
}	
