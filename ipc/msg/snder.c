#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "proto.h"

int main(void)
{
	key_t key;
	int msgid;
	msg_st msg;
	int send;
	key = ftok(PATHNAME, PROJID);
	
	msgid = msgget(key, 0);
	if(msgid < 0)
	{
		perror("msgget()");
		exit(1);
	}	
	
	msg.mtype = 1;
	strcpy(msg.name, "aniu");
	msg.chinese = 130;
	msg.english = 149;

	send = msgsnd(msgid, &msg, sizeof(msg)-sizeof(long), 0);
	if(!send)
		puts("ok!");

	exit(0);
}
