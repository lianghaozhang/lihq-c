#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "proto.h"

static int msgid;

static void sigint_handler(int i)
{
	msgctl(msgid, IPC_RMID, NULL);
}



int main(void)
{
	key_t key;
	msg_path_st msg_path;
	msg_s2c_st msg_s2c;
	ssize_t nob;
	char str[1024] = "我是服务器，我接受到你发送的数据：";
	int fd;
	int len;
	char buf[BUFSIZE];
	signal(SIGINT, sigint_handler);

	while(1)	
	{
		key = ftok(PATH, PROJID);
		msgid = msgget(key, IPC_CREAT | 0600);

		//接收用户传过来的参数
		nob = msgrcv(msgid, &msg_path, sizeof(msg_path), 0, 0);
		if(nob < 0)
		{
			perror("msgrcv()");
			exit(1);
		}
	
		fd = open(msg_path.path, O_RDONLY);	
	
		while((len = read(fd, buf, BUFSIZE)) > 0)
		{
			msg_s2c.mtype = MSG_S2C;
			strncpy(msg_s2c.data, buf, len);
			msgsnd(msgid, &msg_s2c, sizeof(msg_s2c), 0);
		}

		msg_s2c.mtype = MSG_EOT;
		msgsnd(msgid, &msg_s2c, sizeof(msg_s2c), 0);
		
		close(fd);	
	}

	exit(0);
}
