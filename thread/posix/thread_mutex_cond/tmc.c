#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "tmc.h"


tmc_t* tmc_init(int value)
{
	tmc_t* tmc;
	tmc = malloc(sizeof(*tmc));
	if(tmc == NULL)
		return NULL;

	tmc->value = value;
	pthread_mutex_init(&tmc->mut, NULL);
	pthread_cond_init(&tmc->cond, NULL);

	return tmc;
}



int tmc_add(tmc_t* tmc, int n)
{
	pthread_mutex_lock(&tmc->mut);
	tmc->value += n;
	//让每个在等待资源的线程都起来抢锁，看谁够了谁就用
	pthread_cond_broadcast(&tmc->cond);
	pthread_mutex_unlock(&tmc->mut);

	return n;
}

int tmc_sub(tmc_t* tmc, int n)
{
	pthread_mutex_lock(&tmc->mut);
	while(tmc->value < n)
		pthread_cond_wait(&tmc->cond, &tmc->mut);

	tmc->value -= n;
	pthread_mutex_unlock(&tmc->mut);	

	return n;
}

int tmc_destroy(tmc_t* tmc)
{
	if(tmc != NULL)
	{
		pthread_mutex_destroy(&tmc->mut);
		pthread_cond_destroy(&tmc->cond);
		free(tmc);
	}
	
	return 0;
}

