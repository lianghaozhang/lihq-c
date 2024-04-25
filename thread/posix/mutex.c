#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define THRNUM	4

static pthread_mutex_t mut[THRNUM];

static void* func(void* v)
{
	int n = (int)v;
	int c = 'a' + n;
	int next = n == 3 ? 0 : n + 1;
	while(1)
	{
		pthread_mutex_lock(mut + n);
		//write是以ASCII码的形式输出，所以输出的是字符
		write(1, &c, 1);
		pthread_mutex_unlock(mut + next);
	}
}

int main(void)
{
	pthread_t tid[THRNUM];
	int i, err;
	for(i = 0; i < THRNUM; i++)
	{
		pthread_mutex_init(mut + i, NULL);
		pthread_mutex_lock(mut + i);
		err = pthread_create(tid + i, NULL, func, (void*)i);
		if(err)
		{
			fprintf(stdout, "pthread_create(): %s\n", strerror(err));
			exit(1);
		}
		
	}

	pthread_mutex_unlock(mut);
	alarm(1);
	for(i = 0; i < THRNUM; i++)
		pthread_join(tid[i], NULL);


	exit(0);
}
