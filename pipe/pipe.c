#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#define BUFSIZE	1024

int main(void)
{
	pid_t pid;
	int pfd;
	int pipefd[2];
	pfd = pipe(pipefd);
	char stdin_buf[BUFSIZE];
	char buf[BUFSIZE];
	int len;
	if(pfd < 0)
	{
		perror("pipe()");
		exit(1);
	}
	

	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid > 0)	//parent read
	{
		close(pipefd[1]);
		fprintf(stdout, "这里是父进程\n");
		len = read(pipefd[0], buf, BUFSIZE);
		fprintf(stdout, "父进程收到消息：%s\n", buf);
		close(pipefd[0]);
		wait(NULL);
	}
	else	//child write
	{
		close(pipefd[0]);
		fprintf(stdout, "这里是子进程\n");
		fprintf(stdout, "子进程发送信息：HELLO!\n");
		write(pipefd[1], "HELLO!\n", 7);
		close(pipefd[1]);
		exit(0);
	}

	exit(0);
}
