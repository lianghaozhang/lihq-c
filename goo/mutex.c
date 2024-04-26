#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define THRNUM	4

static pthread_mutex_t	mut[THRNUM];
static void* func(void* v)
{
	int c = *(int*)v;
	int m = 'a' + c;
	int n = c == 3 ? 0 : c + 1;
	while(1)
	{
		pthread_mutex_lock(mut + c);
		write(1, &m, 1);
		pthread_mutex_unlock(mut + n);
	}
	pthread_exit(NULL);
}


int main(void)
{
	int i, err;
	pthread_t tid[THRNUM];
	int* arg;
	for(i = 0; i < THRNUM; i++)
	{
		arg = malloc(sizeof(*arg));
		if(arg == NULL)
			exit(1);
		*arg = i;
		pthread_mutex_init(mut + i, NULL);
		pthread_mutex_lock(mut + i);
		err = pthread_create(tid + i, NULL, func, arg);
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
