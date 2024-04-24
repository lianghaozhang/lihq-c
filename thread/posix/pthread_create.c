#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static void* f(void*);

int main(void)
{
	int err;
	puts("Start!");
	pthread_t tid;
	err = pthread_create(&tid, NULL, f, NULL);
	if(err)
	{
		fprintf(stdout, "pthread_create(): %s\n", strerror(err));
		exit(1);
	}
	//等着给线程收尸
	pthread_join(tid, NULL);
	puts("End!");
	exit(0);
}


static void* f(void*)
{
	fprintf(stdout, "Thread is working...\n");
	//结束当前线程，和return不同的是使用这个函数结束线程会自动清理线程栈
	pthread_exit(NULL);
	//return NULL;
}
