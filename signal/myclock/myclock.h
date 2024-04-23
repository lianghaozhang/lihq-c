#ifndef MYCLOCK_H__
#define MYCLOCK_H__

#if 0
	功能模块：
		添加闹钟，删除闹钟

	存储结构：数组
	Clock结构体成员：
		int sec：倒计时秒数
		char* msg：事件显示信息
		void (*func)(char*)：事件
		int flag：标志位->（1.正常 0.结束 -1.暂停）
#endif

#define JOBLISTSIZE	1024

typedef void (*sighandler_t)(int);

typedef struct
{
	int sec;
	char* msg;
	void (*func)(char* s);
	int flag;
	int pos;
} Clock;


static Clock* joblist[JOBLISTSIZE];
static sighandler_t alrm_handler_old;
static int o = 1;

int addClock(int sec, char* msg, void(*func)(char* s));
//int deleteClock(int);
static int findfree(void);
static void alrm_handler(int);
void showJob(void);
static void module_init(void);
static void module_destroy(void);
static void alrm_hander(int);



#endif
