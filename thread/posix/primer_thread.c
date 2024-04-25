#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LEFT	30000000
#define RIGHT	30000200
#define THRNUM	(RIGHT - LEFT + 1)

static void* f(void*);

typedef struct
{
	int num;
} Pthread_arg_t;

int main(void)
{
	int i;
	int err;
	pthread_t tid[THRNUM];
	int* temp;
	void* ret;
	//Pthread_arg_t* pat;
	for(i = LEFT; i < RIGHT; i++)
	{
		temp = malloc(sizeof(*temp));
		//pat = malloc(sizeof(*pat));
		//if(pat == NULL)
		if(temp == NULL)
		{
			perror("malloc()");
			exit(1);
		}
		
		*temp = i;
		//pat->num = i;
		//err = pthread_create(tid + (i - LEFT), NULL, f, pat);
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

	exit(0);
}


static void* f(void* v)
{
	int i, j, flag;
	//j = ((Pthread_arg_t*)v)->num;
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
	
	pthread_exit(v);
}
