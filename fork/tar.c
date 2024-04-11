#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	fprintf(stdout, "this is tar.c start!\n");
	
	int i;
	for(i = 0; i < argc; i++)
		fprintf(stdout, "argv[%d] = %s\n", i, argv[i]);

	fprintf(stdout, "this is tar.c end!\n");

	exit(0);
}
