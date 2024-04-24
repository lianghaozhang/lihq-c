#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

static void int_handler(int);
static void alrm_handler(int);

int main(void)
{
	int i;
	/*
	struct itimerval itv;
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	signal(SIGALRM, alrm_handler);
	*/
	
	signal(SIGINT, int_handler);
	sigset_t set, oset, saveset;
	sigaddset(&set, SIGINT);
	//开始模块前保存信号的初始信息，结束模块时要进行恢复
	sigprocmask(SIG_UNBLOCK, &set, &saveset);
	while(1)
	{
		//sigprocmask(SIG_BLOCK, &set, NULL);
		//阻塞set集合前将set集合中的信号集的状态保存
		sigprocmask(SIG_BLOCK, &set, &oset);
		for(i = 0; i < 5; i++)
		{
			write(1, "*", 1);
			/*
			if(setitimer(ITIMER_REAL, &itv, NULL) < 0)
			{
				perror("setitimer()");
				exit(1);
			}
			*/
			sleep(1);
		}
		write(1, "\n", 1);
		//sigprocmask(SIG_UNBLOCK, &set, NULL);
		//恢复到oset信号集的状态
		sigprocmask(SIG_SETMASK, &oset, NULL);
	}
	
	//结束模块时恢复信号集的初始状态
	sigprocmask(SIG_SETMASK, &saveset, NULL);
	exit(0);
}


static void int_handler(int s)
{
	write(1, "!", 1);
}

static void alrm_handler(int s){}


