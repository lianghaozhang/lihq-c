#ifndef __LS_F_H_
#define __LS_F_H_

#include <glob.h>

void ls(glob_t*);
void print(glob_t*);
void print_ls_l(glob_t*);
void print_ls_n(glob_t*);
void ls_l(void);
void ls_n(void);
void splitPath(char*);
void print(glob_t*);
void fileInfo(const char*);
void fileInfo_n(const char*);


#endif
