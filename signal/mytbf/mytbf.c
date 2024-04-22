#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#include "mytbf.h"

#define JOBMAX	1024

typedef void (*sighandler_t)(int);

static Tbf* job[JOBMAX];
static int flag = 0;
static sighandler_t alrm_handler_old;

static int findfree(void);
static void module_load(void);
static void module_unload(void);
static void alrm_handler(int);


Tbf* tbf_init(int cps, int burst)
{
	Tbf* tbf;
	tbf = malloc(sizeof(*tbf));
	if(tbf == NULL)
		return NULL;
	
	if(!flag)
	{
		signal(SIGALRM, alrm_handler);
		alarm(1);
		flag = 1;
	}	

	int pos = findfree();
	if(pos < 0)
		return NULL;

	tbf->cps = cps;
	tbf->burst = burst;
	tbf->token = 0;
	tbf->pos = pos;
	
	job[pos] = tbf;
	return tbf;
}

#if 0
	获取令牌
#endif
int tbf_getToken(Tbf* tbf, int size)
{	
	//需要token小于0直接报错
	if(size <= 0)
		return -EINVAL;;

	
	//当结构体中没有token时将阻塞进程，等待有token再继续进行
	while(tbf->token <= 0)
		//puts("zuseing...");
		pause();

	int n = tbf->token >= size ? size : tbf->token;
	tbf->token -= n;
	return n;
}

#if 0
	返回多余的令牌
#endif
int tbf_returnToken(Tbf* tbf, int size)
{
	if(size <= 0)
		return -EINVAL;
	
	tbf->token += size;
	if(tbf->token > tbf->burst)
		tbf->token = tbf->burst;

	return size;
}


static int findfree(void)
{
	int i;
	for(i = 0; i < JOBMAX; i++)
	{
		if(job[i] == NULL)
			return i;
	}

	return -1;
}
                                                                                                
int tbf_destroy(Tbf* tbf)
{
	job[tbf->pos] = NULL;
	free(tbf);	
	tbf = NULL;
}


static void module_load(void)
{
	signal(SIGALRM, alrm_handler);
	alarm(1);
	
	atexit(module_unload);
}

static void module_unload(void)
{
	int i;
 	for(i = 0; i < JOBMAX; i++)
	{
		if(job[i] != NULL)
			free(job[i]);
	}

	signal(SIGALRM, alrm_handler_old);
}


static void alrm_handler(int s)
{
	int i;
	for(i = 0; i < JOBMAX; i++)
	{
		if(job[i] != NULL)
		{
			job[i]->token += job[i]->cps;
			if(job[i]->token > job[i]->burst)
				job[i]->token = job[i]->burst;
		}
	}
	
	alarm(1);
}

