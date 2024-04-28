#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "tmc.h"

#define LEFT	30000000
#define RIGHT	30000200
#define THRNUM	(RIGHT - LEFT + 1)
#define N		4



static tmc_t* tmc;
static void* f(void*);


int main(void)
{
	int i, err;
	pthread_t tid[THRNUM];
	int* temp;
	void* ret;

	tmc = tmc_init(N);
	if(tmc == NULL)
	{
		fprintf(stdout, "tmc_init() failed!\n");
		exit(1);
	}

	for(i = LEFT; i < RIGHT; i++)
	{
		temp = malloc(sizeof(*temp));
		if(temp == NULL)
		{
			perror("malloc()");
			exit(1);
		}
		
		*temp = i;
		tmc_sub(tmc, 1);
		err = pthread_create(tid + (i - LEFT), NULL, f, temp);
		if(err)
		{
			fprintf(stdout, "pthread_create(): %s\n", strerror(err));
			exit(1);
		}
	}

	for(i = 0; i < THRNUM - 1; i++)
	{
		pthread_join(tid[i], &ret);
		free(ret);
	}
	
	tmc_destroy(tmc);
	exit(0);
}


static void* f(void* v)
{
	int i, j, flag;
	j = *(int*)v;
	flag = 1;
	for(i = 2; i < j; i++)
	{
		if(j % i == 0)
		{
			flag = 0;
			break;
		}
	}
	if(flag)
		fprintf(stdout, "%d is a primer\n", j);
	
	sleep(10);

	tmc_add(tmc, 1);
	pthread_exit(v);
}
