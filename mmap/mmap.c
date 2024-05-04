#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

//使用mmap将文件信息映射到当前进程的地址空间中
//并统计出有多少个字符a
int main(int argc, char** argv)
{
	int fd;
	int i;
	int count = 0;
	char* data;
	struct stat statres;
	if(argc < 2)
	{
		fprintf(stdout, "Usage...\n");
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	fstat(fd, &statres);
	data = mmap(NULL, statres.st_size, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	for(i = 0; i < statres.st_size; i++)
	{
		if(data[i] == 'a')
			count++;
	}
	
	fprintf(stdout, "a:%d\n", count);
	munmap(data, statres.st_size);
	exit(0);
}
