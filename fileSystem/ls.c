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
static void ls_l();
static void splitPath(char*);


int main(int argc, char** argv)
{
	int c;
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
		//fprintf(stderr, "dev...\n");
		while((c = getopt(argc, argv, "-l")) != -1)
		{
			switch(c)
			{
				case 'l':
					ls_l();					
					break;

			}


		}
	}
	



	exit(0);
}


#if 0
	ls指令的处理函数
#endif
static void ls(glob_t* resglob)
{
	char buf[1024];
	getcwd(buf, 1024);
	char* path = strcat(buf, "/*");
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
	printf("\n");
}

#if 0
	拿到切割后的路径后在这个函数中使用stat函数对文件的属性进行分析，并按照ls -l的格式进行显示
#endif
static void ls_l()
{
	char buf[1024];
	getcwd(buf, 1024);
	//puts(buf);
	splitPath(buf);
	//puts(buf);
}

#if 0
	该函数将通过getcwd获取到的工作路径前面的绝对路径去掉
只保留当前目录
	参数是要分割的路径
#endif
static void splitPath(char* path)
{
	char *filename = path;
    char *p = filename + strlen(filename) - 1;
    while (p >= filename && (*p != '/')) 
 	 	p--;
	
	strcpy(path, p + 1);	
}






















