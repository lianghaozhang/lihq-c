#ifndef RELAYER_H__
#define RELAYER_H__

#include <pthread.h>

#define BUFSIZE		1024
#define JOBSIZE		10000

//有限状态机的状态枚举类型
enum
{   
    STATE_R = 1,
    STATE_W,
    STATE_EX,
    STATE_T
};

//有限状态机结构体
typedef struct
{
	int state;
	int sfd;
	int dfd;
	char buf[BUFSIZE];
	int len;
	int pos;
	char* errstr;
} rel_fsm_st;

enum
{
	STATE_RUNNING = 1,
	STATE_CANCELED,
	STATE_OVER
};

//任务结构体
typedef struct
{
	int state;
	int fd1;
	int fd2;
	int fd1_save;
	int fd2_save;
	rel_fsm_st* fsm12;
	rel_fsm_st* fsm21;
} rel_job_st;


static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t thr_once = PTHREAD_ONCE_INIT;
static pthread_t tid;
static rel_job_st* job_list[JOBSIZE];

int rel_add_job(int, int);
int rel_cancel_job(int);
int rel_getinfo_job(int, rel_job_st*);



#endif
