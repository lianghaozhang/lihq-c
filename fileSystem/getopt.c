#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define TIMESIZE	1024

int main(int argc, char** argv)
{
#if 0
	int getopt(int argc, char * const argv[],const char *optstring);
#endif

	FILE* fp = NULL;
	time_t mytime;
	struct tm* mytm;
	int c;
	char timestr[TIMESIZE];
	char time1[1024];
	time(&mytime);
	mytm = localtime(&mytime);
	timestr[0] = '\0';
	while((c = getopt(argc, argv, "-ty:md")) != -1)
	{
		switch(c)
		{
			case 't':
				strncat(timestr, "%Y-%m-%d", TIMESIZE);
				break;
			case 'y':
				if(strcmp(optarg, "2") == 0)
					strncat(timestr, "%y ", TIMESIZE);
				else if(strcmp(optarg, "4") == 0)
					strncat(timestr, "%Y ", TIMESIZE);
				else
					fprintf(stdout, "error argv...\n");
				break;
			case 'm':
				strncat(timestr, "%m ", TIMESIZE);
				break;
			case 'd':
				strncat(timestr, "%d ", TIMESIZE);
				break;
			case 1:
				fp = fopen(argv[optind - 1], "w");
				if(fp == NULL)
				{
					perror("fopen()");
					fp = stdout;
				}
				break;			
			default:
				break;
		}
	
	}

	strftime(time1, 1024, timestr, mytm);	
	fprintf(fp, "%s\n", time1);
	if(fp != stdout)
		fclose(fp);		
	exit(0);
}
