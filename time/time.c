#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMESIZE	1024

int main(void)
{
	time_t mytime;
	struct tm* mytm;
	char buf[TIMESIZE];
	//获取时间戳
	time(&mytime);
	//将时间戳转换成tm类型的结构体，方便使用
	mytm = localtime(&mytime);
	//strftime函数的参数：格式化输出存储的串的位置，存储大小，格式化字符串，以什么格式输出，tm类型的结构体
	//%H表示已24小时制输出小时
	//strftime(buf, TIMESIZE, "%Y-%m-%d %H:%M:%S", mytm);
	//%I表示以12小时制输出小时
	//strftime(buf, TIMESIZE, "%Y-%m-%d %I:%M:%S", mytm);
	//%T等价于%H:%M:%S
	strftime(buf, TIMESIZE, "%Y-%m-%d %T", mytm);
	puts(buf);
	exit(0);
}
