#ifndef TMC_H__
#define TMC_H__

typedef struct
{
	int value;
	pthread_mutex_t	mut;
	pthread_cond_t cond;
} tmc_t;


tmc_t* tmc_init(int);

int tmc_add(tmc_t*, int);

int tmc_sub(tmc_t*, int);

int tmc_destroy(tmc_t*);



#endif
