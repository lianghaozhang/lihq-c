#include <stdio.h>

int main(){
	printf("hello world!\n");
	//#define ooo
	#ifdef ooo
	#include "aaa.h"
	#endif
	return 0;
}
