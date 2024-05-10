#ifndef	PROTO_H__
#define PROTO_H__

#define PATHNAME	"./a"
#define PROJID		'q'

typedef void (*sighandler_t)(int);

typedef struct
{
	long mtype;
	char name[10];
	int chinese;
	int english;
} msg_st;




#endif
