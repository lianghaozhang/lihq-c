#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define TTY1	"/dev/tty11"
#define TTY2	"/dev/tty12"
#define BUFESIZE	1024

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
	//状态
	int state;
	//源文件描述符
	int sfd;
	//目标文件描述符
	int dfd;
	//缓冲区
	char buf[BUFESIZE];
	//文件读入字节数
	int len;
	int pos;
	char* errstr;
} fsm_st;

//数据中继
static void relay(int, int);
//有限状态机驱动函数
static void fsm_driver(fsm_st*);


int main(void)
{
	int fd1, fd2;
	fd1 = open(TTY1, O_RDWR);	
	if(fd1 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd1, "TTY1\n", 5);

	fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
	if(fd2 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd2, "TTY2\n", 5);

	relay(fd1, fd2);

	close(fd2);
	close(fd1);
	
	exit(0);
}



static void relay(int fd1, int fd2)
{
	int fd1_save, fd2_save;
	int max;
	fsm_st* fsm12;
	fsm_st* fsm21;
	fd_set rs;
	fd_set ws;
	//要求以非阻塞方式打开文件，为了不限制用户在这里使用fcntl函数对文件描符进行修改，改成以非阻塞形式打开文件
	fd1_save = fcntl(fd1, F_GETFL);
	//注意第二个参数是F_SETFL不是F_SETFD，F_SETFL是设置文件状态标志，F_SETFD是设置文件描述符
	fcntl(fd1, F_SETFL, fd1_save | O_NONBLOCK);
		
	fd2_save = fcntl(fd2, F_GETFL);
	fcntl(fd2, F_SETFL, fd2_save | O_NONBLOCK);
	fsm12 = malloc(sizeof(*fsm12));	
	fsm21 = malloc(sizeof(*fsm21));	

	fsm12->sfd = fd1;
	fsm12->dfd = fd2;
	fsm12->state = STATE_R;
	
	fsm21->sfd = fd2;
	fsm21->dfd = fd1;
	fsm21->state = STATE_R;	
	
	//驱动有限状态机
	while(fsm12->state != STATE_T || fsm21->state != STATE_T)
	{
		//布置监视任务
		FD_ZERO(&rs);
		FD_ZERO(&ws);

		if(fsm12->state == STATE_R)
			FD_SET(fsm12->sfd, &rs);
		if(fsm12->state == STATE_W)
			FD_SET(fsm12->dfd, &ws);
		if(fsm21->state == STATE_R)
			FD_SET(fsm21->sfd, &rs);
		if(fsm21->state == STATE_W)
			FD_SET(fsm21->dfd, &ws);

		max = fd1 > fd2 ? fd1 : fd2;
		
		//监视
		if(select(max + 1, &rs, &ws, NULL, NULL) < 0)
		{
			if(errno == EINTR)
				continue;
			perror("select()");
			exit(1);
		}

		//查看监视结果
		if(FD_ISSET(fsm12->sfd, &rs) || FD_ISSET(fsm12->dfd, &ws))
			fsm_driver(fsm12);
		if(FD_ISSET(fsm21->sfd, &rs) || FD_ISSET(fsm21->dfd, &ws))
			fsm_driver(fsm21);
	}

	//模块结束后恢复文件描述符的原始状态	
	fcntl(fd1, F_SETFL, fd1_save);
	fcntl(fd2, F_SETFL, fd2_save);
}


static void fsm_driver(fsm_st* fsm)
{
	int ret;
	switch(fsm->state)
	{
		//读状态时会有四种情况
		case STATE_R:
			fsm->len = read(fsm->sfd, fsm->buf, BUFESIZE);
			//1.当读到的字节数小于0时表示出错了，但是要判断是真错还是假错
			if(fsm->len < 0)
			{
				//当errno为EAGAIN时为假错，表示当前没有可读的数据，所以还需要再读一次，所以把状态设置成读
				if(errno == EAGAIN)
					fsm->state = STATE_R;
				else
				{
					fsm->errstr = "read()";
					fsm->state = STATE_EX;
				}
			}
			else if(fsm->len == 0)
				fsm->state = STATE_T;
			else
			{
				fsm->pos = 0;
				fsm->state = STATE_W;	
			}
			break;
	
		case STATE_W:
			ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_EX;
				}
			}
			else
			{
				fsm->pos += ret;
				fsm->len -= ret;
				if(fsm->len == 0)
					fsm->state = STATE_R;
				else
					fsm->state = STATE_W;
			}
			break;

		case STATE_EX:
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;

		case STATE_T:
			//...
			break;

		default:
			abort();
			break;
	}


}



