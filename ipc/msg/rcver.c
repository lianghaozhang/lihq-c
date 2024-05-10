#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

#include "proto.h"

static void sigint_handler(int);

static int msgid;

int main(void)
{
	key_t key;
	ssize_t nob;
	msg_st msg;
	//获取keyid
	key = ftok(PATHNAME, PROJID);
	
	signal(SIGINT, sigint_handler);
	msgid = msgget(key, IPC_CREAT | 0600);
	if(msgid < 0)
	{
		perror("msgget()");	
		exit(1);
	}
	

	while(1)
	{
		nob = msgrcv(msgid, &msg, sizeof(msg)-sizeof(long), 0, 0);
		if(nob < 0)
		{
			perror("msgrcv()");
			exit(1);
		}
		
		fprintf(stdout, "name=%s\nchinese=%d\nenglish=%d\n", msg.name, msg.chinese, msg.english);
	}

	exit(0);
}


static void sigint_handler(int i)
{
	msgctl(msgid, IPC_RMID, NULL);
}
