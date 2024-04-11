#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE	1024

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stdout, "argv[1]=src, argv[2]=target\n");
		exit(1);
	}
	
	char* src = argv[1];
	char* target = argv[2];
	FILE* src_fp = fopen(src, "r");
	FILE* target_fp = fopen(target, "w");
	char buf[MAXSIZE];
	while(fgets(buf, MAXSIZE, src_fp) != NULL)
		fputs(buf, target_fp);

	fclose(target_fp);
	fclose(src_fp);

	exit(0);
}
