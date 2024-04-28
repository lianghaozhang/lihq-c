#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "mytbf.h"

#define JOBMAX	1024

//typedef void (*sighandler_t)(int);

static Tbf* job[JOBMAX];
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
static	pthread_t tid_load;
static pthread_once_t tid_once = PTHREAD_ONCE_INIT;

//static int flag = 0;
//static sighandler_t alrm_handler_old;

static int findfree_unlocked(void);
static void module_load(void);
static void module_unload(void);
static void* thr_alrm(void*);


Tbf* tbf_init(int cps, int burst)
{
	Tbf* tbf;
	tbf = malloc(sizeof(*tbf));
	if(tbf == NULL)
		return NULL;
	/*
	if(!flag)
	{
		signal(SIGALRM, alrm_handler);
		alarm(1);
		flag = 1;
	}	
	*/

	pthread_once(&tid_once, module_load);

	tbf->cps = cps;
	tbf->burst = burst;
	tbf->token = 0;
	//初始化互斥量
	pthread_mutex_init(&tbf->mut, NULL);
	
	pthread_mutex_lock(&mut_job);
	int pos = findfree_unlocked();
	if(pos < 0)
	{
		pthread_mutex_unlock(&mut_job);
		return NULL;
	}

	tbf->pos = pos;
	job[pos] = tbf;
	pthread_mutex_unlock(&mut_job);

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

	
	pthread_mutex_lock(&tbf->mut);
	//当结构体中没有token时将阻塞进程，等待有token再继续进行
	while(tbf->token <= 0)
		pthread_mutex_unlock(&tbf->mut);
		sched_yield();
		pthread_mutex_lock(&tbf->mut);

	int n = tbf->token >= size ? size : tbf->token;
	tbf->token -= n;
	pthread_mutex_unlock(&tbf->mut);
	
	return n;
}

#if 0
	返回多余的令牌
#endif
int tbf_returnToken(Tbf* tbf, int size)
{
	if(size <= 0)
		return -EINVAL;
	
	pthread_mutex_lock(&tbf->mut);
	tbf->token += size;
	if(tbf->token > tbf->burst)
		tbf->token = tbf->burst;
	
	pthread_mutex_unlock(&tbf->mut);
	return size;
}


static int findfree_unlocked(void)
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
	pthread_mutex_lock(&mut_job);
	job[tbf->pos] = NULL;
	pthread_mutex_unlock(&mut_job);
	free(tbf);	
	tbf = NULL;

	pthread_cancel(tid_load);
	pthread_join(tid_load, NULL);
}


static void module_load(void)
{
	//signal(SIGALRM, alrm_handler);
	//alarm(1);
	int err;
	err = pthread_create(&tid_load, NULL, thr_alrm, NULL);
	if(err)
	{
		fprintf(stdout, "pthread_create(): %s\n", strerror(err));
		exit(1);
	}

	atexit(module_unload);
}

static void module_unload(void)
{
	int i;
 	for(i = 0; i < JOBMAX; i++)
	{
		if(job[i] != NULL)
			pthread_mutex_destroy(&job[i]->mut);
			free(job[i]);
	}
	
	pthread_mutex_destroy(&mut_job);
	//signal(SIGALRM, alrm_handler_old);
}


static void* thr_alrm(void* v)
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mut_job);
		for(i = 0; i < JOBMAX; i++)
		{
			if(job[i] != NULL)
			{
				pthread_mutex_lock(&job[i]->mut);
				job[i]->token += job[i]->cps;
				if(job[i]->token > job[i]->burst)
					job[i]->token = job[i]->burst;
				pthread_mutex_unlock(&job[i]->mut);
			}
		}
		pthread_mutex_unlock(&mut_job);

		sleep(1);
	}
	//alarm(1);
}

