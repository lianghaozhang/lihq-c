#include <stdio.h>
#include <stdlib.h>

int main(void)
{	
	int y = 2024;
	int m = 3;
	int d = 24;
	
	char time[1024];
	sprintf(time, "%d-%d-%d", y, m, d);
	puts(time);
	exit(0);
}
