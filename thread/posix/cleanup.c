#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


static void func(void* v)
{
	puts(v);
}



static void* f(void* v)
{
	fprintf(stdout, "Thread is working...\n");
	pthread_cleanup_push(func, "pthread_cleanup_push(): 1");
	pthread_cleanup_push(func, "pthread_cleanup_push(): 2");
	pthread_cleanup_push(func, "pthread_cleanup_push(): 3");

	//return NULL;
	pthread_exit(NULL);

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}



int main(void)
{
	puts("Start!");
	int err;
	pthread_t tid;
	pthread_create(&tid, NULL, f, NULL);
	err = pthread_join(tid, NULL);
	if(err)
	{
		fprintf(stdout, "pthread_join(): %s\n", strerror(err));
		exit(1);
	}
	puts("End!");
	exit(0);
}
