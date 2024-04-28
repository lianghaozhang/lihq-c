#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define LEFT	30000000
#define RIGHT	30000200
#define THRNUM	4

//0：没有任务 1：有任务 -1：全部任务完成，提示线程结束
static int num = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t con = PTHREAD_COND_INITIALIZER;
static void* func(void* v);

int main(void)
{
	int i, err;
	void* ret;
	int* arg;
	pthread_t tid[THRNUM];
	for(i = 0; i < THRNUM; i++)
	{
		arg = malloc(sizeof(*arg));
		if(arg == NULL)
			exit(1);
		*arg = i;
		err = pthread_create(tid + i, NULL, func, arg);	
		if(err)
		{
			fprintf(stdout, "pthread_create(): %s\n", strerror(err));
			exit(1);
		}
	}	

	//下发任务
	for(i = LEFT; i < RIGHT; i++)
	{
		pthread_mutex_lock(&mut);
		while(num != 0)
			pthread_cond_wait(&con, &mut);

		num = i;
		//给下游发消息
		pthread_cond_signal(&con);
		pthread_mutex_unlock(&mut);
	}

	pthread_mutex_lock(&mut);
	while(num != 0)
		pthread_cond_wait(&con, &mut);
	
	num = -1;
	//给下游发消息
	pthread_cond_broadcast(&con);
	pthread_mutex_unlock(&mut);
	
	
	for(i = 0; i < THRNUM; i++)
	{
		pthread_join(tid[i], &ret);
		free(ret);
	}

	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&con);
	exit(0);
}


static void* func(void* v)
{
	int i, j, flag;
	
	while(1)
	{
		pthread_mutex_lock(&mut);
		if(num == -1)
		{
			pthread_mutex_unlock(&mut);
			break;	
		}	
		
		while(num == 0)
			pthread_cond_wait(&con, &mut);

		j = num;
		num = 0;
		//给上游发消息
		pthread_cond_broadcast(&con);
		pthread_mutex_unlock(&mut);

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
			fprintf(stdout, "[%d] %d is primer\n", *(int*)v, j);
	}	

	pthread_exit(v);
}

