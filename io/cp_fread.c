#if 0
	使用fread()和fwrite()函数实现命令cp src dest的文件复制功能
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE	1024

int main(int argc, char* argv[])
{
	char buf[BUFSIZE];
	int item;
	if(argc < 3)
	{
		printf("缺少必要参数，用法：%s src dest\n", argv[0]);
		exit(1);
	}

	FILE *fps, *fpd = NULL;
	fps = fopen(argv[1], "r");
	if(fps == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	
	fpd = fopen(argv[2], "w");
	if(fpd == NULL)
	{
		fclose(fps);
		perror("fopen()");
		exit(1);
	}

	while((item = fread(buf, 1, BUFSIZE, fps)) > 0)
	{
		fwrite(buf, 1, item, fpd);
	}

	fclose(fpd);
	fclose(fps);

	exit(0);
}
