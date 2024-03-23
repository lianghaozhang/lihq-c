#if 0
	使用fgetc()和fputc()函数实现命令cp src dest的文件复制功能
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	int ch;
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

	while(1)
	{
		ch = fgetc(fps);
		if(ch == EOF)
			break;
		fputc(ch, fpd);
	}

	fclose(fpd);
	fclose(fps);

	exit(0);
}
