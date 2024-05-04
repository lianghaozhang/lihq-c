#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXSIZE	1024

//父子进程间使用mmap进行通信
int main(void)
{
	pid_t pid;
	char* ptr;
	ptr = mmap(NULL, MAXSIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap()");
		exit(1);
	}

	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}


	if(pid == 0) //child
	{
		strcpy(ptr, "hello!");
		munmap(ptr, MAXSIZE);
		exit(0);
	}
	else		//paren
	{
		wait(NULL);
		puts(ptr);
		munmap(ptr, MAXSIZE);
		exit(0);
	}
}
