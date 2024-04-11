#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>
#include "ls_f.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#if 0
	ls指令的处理函数，不带选项和参数
#endif
void ls(glob_t* resglob)
{
	char buf[1024];
	getcwd(buf, 1024);
	char* path = strcat(buf, "/*");
	glob(path, 0, NULL, resglob);	
}


void print(glob_t* glob)
{
	int i;
	for(i = 0; i < glob->gl_pathc; i++)
	{
		const char *filename = glob->gl_pathv[i];
        const char *p = filename + strlen(filename) - 1;
        while (p >= filename && (*p != '/')) 
        	p--;
        fprintf(stdout, "%s  ", p + 1);

	}
	printf("\n");
}

void fileInfo(const char* path)
{
	struct stat statres;
	char info[1024];
	struct passwd* pw;
	struct group* gp;
	char* user;
	char* group;
	//int lstat(const char *pathname, struct stat *statbuf);
	lstat(path, &statres);
	//文件的类型和模式
	mode_t m = statres.st_mode;
	//文件的硬链接数
	nlink_t hardLink = statres.st_nlink;
	//文件的uid
	uid_t uid = statres.st_uid;
	//通过uid获取用户名，使用函数getpwuid
	pw = getpwuid(uid);
	if(pw == NULL)
	{
		perror("getpwuid()");
		exit(1);
	}
	user = pw->pw_name;

	//文件的gid
	//获取组名
	gid_t gid = statres.st_gid;
	gp = getgrgid(gid);
	if(gp == NULL)
	{
		perror("getgrgid()");
		exit(1);
	}
	group = gp->gr_name;

	info[0] = S_ISDIR(m) ? 'd' : '-';
	info[1] = (m & S_IRUSR) ? 'r' : '-';
    info[2] = (m & S_IWUSR) ? 'w' : '-';
    info[3] = (m & S_IXUSR) ? 'x' : '-';
    info[4] = (m & S_IRGRP) ? 'r' : '-';
    info[5] = (m & S_IWGRP) ? 'w' : '-';
    info[6] = (m & S_IXGRP) ? 'x' : '-';
    info[7] = (m & S_IROTH) ? 'r' : '-';
    info[8] = (m & S_IWOTH) ? 'w' : '-';
    info[9] = (m & S_IXOTH) ? 'x' : '-';
	info[10] = '\0';

	char timefm[1024];
	//strftime(timefm, 1024, "%-m %-d %H:%M", localtime(&statres.st_mtime));
	strftime(timefm, 1024, "%-m %-d %H:%M", localtime(&statres.st_mtime));
	fprintf(stdout, "%s %ld %s %s %5ld  %s  ", info, hardLink, user, group, statres.st_size, timefm);
}

void fileInfo_n(const char* path)
{
	struct stat statres;
	char info[1024];
	lstat(path, &statres);
	//文件的类型和模式
	mode_t m = statres.st_mode;
	//文件的硬链接数
	nlink_t hardLink = statres.st_nlink;
	//文件的uid
	uid_t uid = statres.st_uid;
	//文件的gid
	gid_t gid = statres.st_gid;
	
	info[0] = S_ISDIR(m) ? 'd' : '-';
	info[1] = (m & S_IRUSR) ? 'r' : '-';
    info[2] = (m & S_IWUSR) ? 'w' : '-';
    info[3] = (m & S_IXUSR) ? 'x' : '-';
    info[4] = (m & S_IRGRP) ? 'r' : '-';
    info[5] = (m & S_IWGRP) ? 'w' : '-';
    info[6] = (m & S_IXGRP) ? 'x' : '-';
    info[7] = (m & S_IROTH) ? 'r' : '-';
    info[8] = (m & S_IWOTH) ? 'w' : '-';
    info[9] = (m & S_IXOTH) ? 'x' : '-';
	info[10] = '\0';

	char timefm[1024];
	strftime(timefm, 1024, "%-m %-d %H:%M", localtime(&statres.st_mtime));
	fprintf(stdout, "%s %ld %d %d %5ld  %s  ", info, hardLink, uid, gid, statres.st_size, timefm);
}


void print_ls_l(glob_t* glob)
{
	int i;
	for(i = 0; i < glob->gl_pathc; i++)
	{
		const char *filename = glob->gl_pathv[i];
		fileInfo(filename);
        const char *p = filename + strlen(filename) - 1;
        while (p >= filename && (*p != '/')) 
        	p--;
        fprintf(stdout, "%s\n", p + 1);

	}
}


void print_ls_n(glob_t* glob)
{
	int i;
	for(i = 0; i < glob->gl_pathc; i++)
	{
		const char *filename = glob->gl_pathv[i];
		fileInfo_n(filename);
        const char *p = filename + strlen(filename) - 1;
        while (p >= filename && (*p != '/')) 
        	p--;
        fprintf(stdout, "%s\n", p + 1);

	}
}

#if 0
	拿到切割后的路径后在这个函数中使用stat函数对文件的属性进行分析，并按照ls -l的格式进行显示
#endif
void ls_l(void)
{
	char buf[1024];
	getcwd(buf, 1024);
	//splitPath(buf);
	//puts(buf);
	strcat(buf, "/*");
	//puts(buf);
	glob_t globres;
	glob(buf, 0, NULL, &globres);
	print_ls_l(&globres);
}

void ls_n(void)
{
	char buf[1024];
	getcwd(buf, 1024);
	//splitPath(buf);
	//puts(buf);
	strcat(buf, "/*");
	//puts(buf);
	glob_t globres;
	glob(buf, 0, NULL, &globres);
	print_ls_n(&globres);
}

#if 0
	该函数将通过getcwd获取到的工作路径前面的绝对路径去掉
只保留当前目录
	参数是要分割的路径
#endif
void splitPath(char* path)
{
	char *filename = path;
    char *p = filename + strlen(filename) - 1;
    while (p >= filename && (*p != '/')) 
 	 	p--;
	
	strcpy(path, p + 1);	
}

