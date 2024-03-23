#include <stdio.h>

#define MAX(a, b) ({int A = a, B = b; ((A) > (B) ? (A) : (B));})

//#define PI 3.14
int main(void){
	#if 0
	double res;
	double ans;
	int r = 10;
	res = PI * r * r;
	ans = 2 * PI * r;
	printf("面积：%.2f\n",res);
	printf("周长：%.2f\n",ans);
	#endif
	int i = 5, j = 3;
	printf("i = %d, j = %d\n",i,j); //5 3
	printf("%d\n", MAX(i++, j++)); //5
	printf("i = %d, j = %d\n",i,j); //7 4
	return 0;
}
