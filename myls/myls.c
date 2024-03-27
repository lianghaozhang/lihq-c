#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>

#define SIZE	1024

#if 0
int main(void)
{
	char ch[SIZE];
	if(getcwd(ch, SIZE) != NULL)
		fprintf(stdout, "当前工作路径为：%s\n", ch);
	else
		fprintf(stdout, "error\n");

	exit(0);
}
#endif


static void show(glob_t*);

int main(int argc, char** argv)
{
	char ch[SIZE];
	glob_t globres;
	getcwd(ch, SIZE);
	strcat(ch, "/*");
	//fprintf(stdout, "%s\n", ch);
	if(argc < 2)
	{
		glob("./*", 0, NULL, &globres);
		show(&globres);
	}
	else
	{
		fprintf(stdout, "dev...\n");
	}
	exit(0);
}


static void show(glob_t* glob)
{
	int i;
	for(i = 0; i < glob->gl_pathc; i++)
	{
		fprintf(stdout, "%s ", glob->gl_pathv[i]);
	}
	printf("\n");
}
