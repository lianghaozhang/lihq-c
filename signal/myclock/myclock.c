#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "myclock.h"
	

static int findfree(void)
{
	int i;
	for(i = 0; i < JOBLISTSIZE; i++)
	{
		if(joblist[i] == NULL)
			return i;
	}
	
	return -1;
}



int addClock(int sec, char* msg, void (*func)(char* s))
{
	if(sec <= 0)
	{
		fprintf(stdout, "参数错误\n");
		exit(1);
	}

	int index = findfree();
	if(index < 0)
	{
		fprintf(stdout, "闹钟数量达到上限\n");
		exit(1);
	}

	
	Clock* c;
	c = malloc(sizeof(*c));
	if(c == NULL)
	{
		fprintf(stdout, "内存不足\n");
		exit(1);
	}

	c->sec = sec;
	c->msg = msg;
	c->func = func;
	c->flag = 1;
	c->pos = index;

	joblist[index] = c;

	if(o)
		module_init();

	return index;
}

void showJob(void)
{
	int i;
	for(i = 0; i < JOBLISTSIZE; i++)
	{
		if(joblist[i] != NULL && joblist[i]->flag == 1)
			fprintf(stdout, "sec: %d\tmsg: %s\n", joblist[i]->sec, joblist[i]->msg);
	}
}

static void module_init(void)
{
	//fprintf(stdout, "module_init()\n");
	atexit(module_destroy);
	alrm_handler_old = signal(SIGALRM, alrm_handler);
	alarm(1);
	o = 0;
	//fprintf(stdout, "module_init() end\n");
}

static void module_destroy(void)
{
	//fprintf(stdout, "module_destroy()\n");
	int i;
	for(i = 0; i < JOBLISTSIZE; i++)
	{
		if(joblist[i] != NULL)
			free(joblist[i]);
			joblist[i] = NULL;
	}

	signal(SIGALRM, alrm_handler_old);
	alarm(0);
	//fprintf(stdout, "module_destroy() end\n");
}

static void alrm_handler(int a)
{
	//fprintf(stdout, "alrm_handler()\n");
	int i;
	int j = 0;
	for(i = 0; i < JOBLISTSIZE; i++)
	{
		if(joblist[i] != NULL && joblist[i]->flag == 1)
		{
			joblist[i]->sec--;
			if(joblist[i]->sec == 0)
			{	
				joblist[i]->func(joblist[i]->msg);
				joblist[i]->flag = 0;
				j = 1;
			}
		}
	}

	if(!j)
		write(1, ".", 1);

	alarm(1);
	//fprintf(stdout, "alrm_handler() end\n");
}



