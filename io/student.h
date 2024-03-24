#ifndef __STUDENT_H_
#define __STUDENT_H_

typedef struct {
    char sno[30];
    char name[10];
    int age;
} Student;

int add(const Student* );
void showList(void);
void w(void);		
void r(void);
void initStudentList(void);

#endif
