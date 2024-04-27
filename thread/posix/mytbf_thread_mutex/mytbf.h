#ifndef MYTBF_H__
#define MYTBF_H__

#define TBF_MAX	1024

typedef struct
{
	int cps;
	int burst;
	int token;
	int pos;
	pthread_mutex_t mut;
} Tbf;

Tbf* tbf_init(int cps, int burst);
int tbf_getToken(Tbf* tbf, int tokenNum);
int tbf_returnToken(Tbf* tbf, int tokenNum);
int tbf_destroy(Tbf*);


#endif
