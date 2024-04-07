#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>

#if 0
	int glob(const char *pattern, int flags,
                int (*errfunc) (const char *epath, int eerrno),
                glob_t *pglob);      void globfree(glob_t *pglob);
       void globfree(glob_t *pglob);
#endif



static void ls(glob_t*);
static void print(glob_t*);


int main(int argc, char** argv)
{
	char* path = NULL;
	glob_t resglob;
	if(argc == 1)
	{
		//fprintf(stdout, "ls\n");
		ls(&resglob);
		print(&resglob);
	}else if
	((argc >= 2) && (!strcmp(".", argv[1])))
	{
		ls(&resglob);
		print(&resglob);
	}else
	{
		fprintf(stderr, "dev...\n");
	}
	



	exit(0);
}


//static void ls()
static void ls(glob_t* resglob)
{
	char buf[1024];
	getcwd(buf, 1024);
	//fprintf(stdout, "%s\n", buf);
	char* path = strcat(buf, "/*");
	//fprintf(stdout, "%s\n", path);
	glob(path, 0, NULL, resglob);	
}


static void print(glob_t* glob)
{
	int i;
	for(i = 0; i < glob->gl_pathc; i++)
	{
		const char *filename = glob->gl_pathv[i];
        const char *p = filename + strlen(filename) - 1;
        while (p >= filename && (*p != '/')) 
        	p--;
        fprintf(stdout, "%s ", p + 1);

	}
	//	fprintf(stdout, "%s ", glob->gl_pathv[i]);
	printf("\n");
}














