#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>
#include "ls_f.h"


int main(int argc, char** argv)
{
	int c;
	char* path = NULL;
	glob_t resglob;
	if(argc == 1)
	{
		ls(&resglob);
		print(&resglob);
	}else if((argc >= 2) && (!strcmp(".", argv[1])))
	{
		ls(&resglob);
		print(&resglob);
	}else
	{
		while((c = getopt(argc, argv, "-ln")) != -1)
		{
			switch(c)
			{
				case 'l':
					ls_l();					
					break;
				case 'n':
					ls_n();
					break;
			}


		}
	}
	



	exit(0);
}
