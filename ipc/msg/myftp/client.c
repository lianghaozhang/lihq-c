#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

#include "proto.h"

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stdout, "Usage...\n");
		exit(1);
	}

	char* path = argv[1];
	key_t key;
	int msgid;
	msg_path_st msg_path;
	msg_s2c_st msg_s2c;
	int ret_s;
	ssize_t ret_c;

	key = ftok(PATH, PROJID);
	if(key < 0)
	{
		perror("ftok()");
		exit(1);
	}

	msgid = msgget(key, 0);
	if(msgid < 0)
	{
		perror("msgget()");
		exit(1);
	}

	strcpy(msg_path.path, path);
	ret_s = msgsnd(msgid, &msg_path, sizeof(msg_path), 0);
	if(ret_s < 0)
	{
		perror("msgsnd()");
		exit(1);
	}

	while(1)
	{
		ret_c = msgrcv(msgid, &msg_s2c, sizeof(msg_s2c), 0, 0);
		if(ret_c < 0)
		{
			perror("msgrcv()");
			exit(1);
		}

		if(msg_s2c.mtype == MSG_S2C)
			fprintf(stdout, "%s\n", msg_s2c.data);
		
		if(msg_s2c.mtype == MSG_EOT)
			break;	
	}
	
	msgctl(msgid, IPC_RMID, NULL);

	exit(0);
}

