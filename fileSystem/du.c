#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>

#define MAXSIZE	1024

static int mydu(const char*);
static int f(const char*);

int main(int argc, char** argv)
{
	fprintf(stdout, "%d\t%s\n", mydu(argv[1]) / 2, argv[1]);
	exit(0);
}


static int mydu(const char* path)
{
	int i, sum;
	struct stat statres;
	glob_t globres;
	lstat(path, &statres);
	if(!S_ISDIR(statres.st_mode))
		return statres.st_blocks;
	
	char temppath[MAXSIZE];
	strncpy(temppath, path, MAXSIZE);
	strncat(temppath, "/*", MAXSIZE);
	glob(temppath, 0, NULL, &globres);
	
	strncpy(temppath, path, MAXSIZE);
	strncat(temppath, "/.*", MAXSIZE);
	glob(temppath, GLOB_APPEND, NULL, &globres);
	sum = statres.st_blocks;

	for(i = 0; i < globres.gl_pathc; i++)
	{
		if(f(globres.gl_pathv[i]))
		sum += mydu(globres.gl_pathv[i]);	
	}
	
	globfree(&globres);	
	return sum;
}



static int f(const char* pathname)
{
	const char* p = pathname + strlen(pathname) - 1;
	while(*p != '/')
		p--;
	
	if((!strcmp(p + 1, ".")) || (!strcmp(p + 1, "..")))
		return 0;	

	return 1;
}
