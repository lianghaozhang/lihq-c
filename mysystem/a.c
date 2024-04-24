#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	char base[50] = "cp ";
	char src[50] = argv[1];
	char des[50] = strcat(" ", argv[2]);
	char* cmd = strcat(strcat(base, src), des); 
	//char* cmd = strcat(strcat(base, argv[1]), strcat(" ", argv[2]));
	puts(cmd);
	//system(cmd);


	exit(0);
}
