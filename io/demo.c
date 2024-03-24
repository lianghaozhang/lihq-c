#if 0
	创建一个学生表，并将数据写出到students.txt
#endif


#include <stdio.h>
#include <stdlib.h>
#include "student.h"


static Student list[50];
static count = 0;

int main(void)
{
	initStudentList();
	Student s1 = {"229050819", "阿怪", 20};	
	if(add(&s1) == 1)
	{
		fprintf(stdout, "学生添加成功！\n");
	}
	else
	{
		fprintf(stdout, "学生添加失败！\n");
	}

	showList();
	w();
	exit(0);
}


int add(const Student* s)
{
	if(s == NULL)
		return -1;

	list[count] = *s;
	count++;
	return 1;
}


void showList(void)
{
	int i;
	for(i = 0; i < count; i++)
	{
		fprintf(stdout, "sno: %s\tname: %s\tage: %d\n", list[i].sno, list[i].name, list[i].age);
	}	
}


void w(void)
{
	int i;
	FILE* fp = NULL;
	fp = fopen("student_info.txt", "w");
	if(fp != NULL)
	{
		for(i = 0; i < count; i++)
		{
			fprintf(fp, "sno: %s\tname: %s\tage: %d\n", list[i].sno, list[i].name, list[i].age);
		}
		fprintf(stdout, "学生信息已经保存到当前目录下的student_info.txt文件中\n");	
	}
	else
	{
		perror("fopen()");
		return;
	}
	fclose(fp);
}

void r(void)
{
	FILE* fp = NULL;
	fp = fopen("student_info.txt", "r");
	if(fp != NULL)
	{
		while(fscanf(fp, "sno: %s\tname: %s\tage: %d\n", list[count].sno, list[count].name, &list[count].age) == 3)
		{
			count++;
		}
	}
	else
	{
		perror("fopen()");
		return;
	}
	
	fclose(fp);
}

void initStudentList(void)
{
	r();
}




