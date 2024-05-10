#ifndef PROTO_H__
#define PROTO_H__

#define PATH		"a"
#define PROJID		'a'
#define PATHSIZE	1024
#define DATASIZE	4096
#define BUFSIZE		1024

enum
{
	MSG_EOT = 1,
	MSG_S2C
};

typedef struct
{
	char path[PATHSIZE];
} msg_path_st;


typedef struct
{
	long mtype;
	char data[DATASIZE];
} msg_s2c_st;

#endif
