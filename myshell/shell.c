#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <wait.h>
#include <unistd.h>

#define DELIMES	" \t\n"

typedef struct
{
	glob_t globres;

} Cmd;


void parse(char*, Cmd* cmd);


int main(int argc, char** argv)
{
	//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
	char* linebuf = NULL;
	size_t linebuf_size = 0;
//	glob_t globres;
	Cmd cmd;
	pid_t pid;
	
	while(1)
	{
		fprintf(stdout, "[aniu_shell-1.0]$ ");
		
		if(getline(&linebuf, &linebuf_size, stdin) < 0)
			break;
		
		parse(linebuf, &cmd);
		
		//puts(cmd.globres.gl_pathv[0]);	
//	#if 0
		if(0)
		{}
		else
		{
			pid = fork();
			if(pid < 0)
			{
				perror("fork()");
				exit(1);
			}

			if(pid == 0)
			{
				execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
				perror("execvp()");
				exit(1);
			}
			
			wait(NULL);
		}
	
	//#endif
	}

	exit(0);
}


void parse(char* line, Cmd* cmd)
{
	/*
 *
 *	int glob(const char *pattern, int flags,
 *	                int (*errfunc) (const char *epath, int eerrno),
 *	                                glob_t *pglob);
 * */

	char* tok = NULL;
	int i = 0;
	while(1)
	{
		tok = strsep(&line, DELIMES);
		if(tok == NULL)
			break;
		if(tok[0] == '\0')
			continue;

		if(i == 0)
		{
			glob(tok, GLOB_NOCHECK, NULL, &cmd->globres);
			i = 1;
		}
		else
			glob(tok, GLOB_NOCHECK|GLOB_APPEND, NULL, &cmd->globres);
		
	}

	//puts(cmd->globres.gl_pathv[0]);
}


