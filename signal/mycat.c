#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

static void p(char*);
static void p_c(char*, int);
static void p_l(char*);
static void f(int);

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage...\n");
		exit(1);
	}

	if(argc == 2)
		p(argv[1]);
	
	int c;
	signal(SIGALRM, f);
	while((c = getopt(argc, argv, "-lc:")) != -1)
	{
		switch(c)
		{
			case 'c':
				//fprintf(stdout, "-c %s %s\n", optarg, argv[optind]);
				p_c(argv[optind],atoi(optarg));
				break;
			case 'l':
				//fprintf(stdout, "-l %s\n", argv[optind]);
				p_l(argv[optind]);
				break;
		}
	}

	exit(0);
}


static void p(char* fn)
{
	char* buf = NULL;
	size_t bufSize = 0;
	FILE* fp = fopen(fn, "r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	while(getline(&buf, &bufSize, fp) != -1)
	{
		fprintf(stdout, "%s", buf);
	}
	
	fclose(fp);
}





static void p_c(char* fn, int cnum)
{
	int fd;
	char buf[cnum];
	char* filename = fn;
	int i;
	fd = open(filename, O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	while((i = read(fd, buf, cnum)) != 0)
	{
		write(1, buf, i);
		alarm(1);
		pause();
	}
	close(fd);
}



static void p_l(char* fn)
{
	char* buf = NULL;
	size_t bufSize = 0;
	FILE* fp = fopen(fn, "r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	while(getline(&buf, &bufSize, fp) != -1)
	{
		fprintf(stdout, "%s", buf);
		alarm(1);
		pause();
	}
	
	fclose(fp);
}



static void f(int i)
{}










