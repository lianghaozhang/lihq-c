#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "mytbf.h"

#define CPS		10
#define BUFSIZE	1024
#define BURST	100

int main(int argc, char** argv)
{
	int fd;
	char buf[BUFSIZE];
	int  size;
	ssize_t len;
	Tbf* tbf;

	if(argc < 2)
	{
		fprintf(stdout, "Usage...\n");
		exit(1);
	}
	
	//开始操作前先初始化tbf结构体
	tbf = tbf_init(CPS, BURST);
	if(tbf == NULL)
	{
		fprintf(stderr, "tbf_init() return null\n");
		exit(1);
	}	

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	while(1)
	{
		//申请token，申请BUFSIZE个是为了让资源最大利用，size是申请到的token数
		size = tbf_getToken(tbf, BUFSIZE);
		//len是读到的有效字节
		if((len = read(fd, buf, size)) == 0)
			break;
		//写之前判断申请到的token是否用用完，没用完要返回回去
		//当申请到的和read读到的有效字符不相等时表示没有用完申请到的token。所以需要返回
		if(size - len > 0)
			tbf_returnToken(tbf, size - len);		
		write(1, buf, len);
	}

	close(fd);
	tbf_destroy(tbf);

	exit(0);
}


