#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "relayer.h"


static void rel_fsm_driver(rel_fsm_st* fsm)
{
	int ret;
	switch(fsm->state)
	{
		//读状态时会有四种情况
		case STATE_R:
			fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
			//1.当读到的字节数小于0时表示出错了，但是要判断是真错还是假错
			if(fsm->len < 0)
			{
				//当errno为EAGAIN时为假错，表示当前没有可读的数据，所以还需要再读一次，所以把状态设置成读
				if(errno == EAGAIN)
					fsm->state = STATE_R;
				else
				{
					fsm->errstr = "read()";
					fsm->state = STATE_EX;
				}
			}
			else if(fsm->len == 0)
				fsm->state = STATE_T;
			else
			{
				fsm->pos = 0;
				fsm->state = STATE_W;
			}
			break;

		case STATE_W:
			ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_EX;
				}
			}
			else
			{
				fsm->pos += ret;
				fsm->len -= ret;
				if(fsm->len == 0)
					fsm->state = STATE_R;
				else
					fsm->state = STATE_W;
			}
			break;

		case STATE_EX:
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;

		case STATE_T:
			//...
			break;

		default:
			abort();
			break;
	}


}


static void* thr_push_fsm(void* v)
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mut_job);
		for(i = 0; i < JOBSIZE; i++)
		{
			//当有任务而且任务的状态为RUNNING时才去推状态机
			if(job_list[i] != NULL && job_list[i]->state == STATE_RUNNING)
			{
				//推完之后要判断状态机是否已经结束
				rel_fsm_driver(job_list[i]->fsm12);
				rel_fsm_driver(job_list[i]->fsm21);
				//当两个状态机的状态都为STATE_T时表示两个状态机都执行完毕了，所以要将任务状态置为结束OVER
				//下次循环就不会再看这个任务了
				if(job_list[i]->fsm12->state == STATE_T && job_list[i]->fsm21->state == STATE_T)
					job_list[i]->state = STATE_OVER;
			}
		}
		pthread_mutex_unlock(&mut_job);
	}
}


static void module_unload(void)
{
	int i;
	pthread_mutex_destroy(&mut_job);
	pthread_join(tid, NULL);
	for(i = 0; i < JOBSIZE; i++)
	{
		if(job_list[i] != NULL)
			free(job_list[i]);
	}
}

static void module_load(void)
{
	int err;
	err = pthread_create(&tid, NULL, thr_push_fsm, NULL);
	if(err)
	{
		fprintf(stdout, "pthread_create(): %s\n", strerror(err));
		exit(1);
	}
	atexit(module_unload);
}


static int get_free_unlocked(void)
{
	int i;
	for(i = 0; i < JOBSIZE; i++)
	{
		if(job_list[i] == NULL)
			return i;
	}
	return -1;
}


int rel_add_job(int fd1, int fd2)
{
	if(fd1 < 0 || fd2 < 0)
		return -EINVAL;

	pthread_once(&thr_once, module_load);

	int pos;
	//创建一个任务
	rel_job_st* job;
	job = malloc(sizeof(*job));
	if(job == NULL)
		return -ENOMEM;
	//初始化任务
	job->state = STATE_RUNNING;
	job->fd1 = fd1;
	job->fd2 = fd2;

	//将文件描述符设置成非阻塞的
	job->fd1_save = fcntl(job->fd1, F_GETFL);
	fcntl(job->fd1, F_SETFL, job->fd1_save | O_NONBLOCK);
	job->fd2_save = fcntl(job->fd2, F_GETFL);
	fcntl(job->fd2, F_SETFL, job->fd2_save | O_NONBLOCK);

	rel_fsm_st* fsm12;
	rel_fsm_st* fsm21;
	fsm12 = malloc(sizeof(*fsm12));
	if(fsm12 == NULL)
	{
		perror("malloc()");
		exit(1);
	}

	fsm21 = malloc(sizeof(*fsm21));
	if(fsm21 == NULL)
	{
		perror("malloc()");
		exit(1);
	}
	fsm12->state = STATE_R;
	fsm12->sfd = job->fd1;
	fsm12->dfd = job->fd2;
	
	fsm21->state = STATE_R;
	fsm21->sfd = job->fd2;
	fsm21->dfd = job->fd1;

	job->fsm12 = fsm12;
	job->fsm21 = fsm21;
	//在数组中找找到一个下标最小的空位
	pthread_mutex_lock(&mut_job);
	pos = get_free_unlocked();
	if(pos < 0)
	{
		pthread_mutex_unlock(&mut_job);
		fcntl(job->fd1, F_SETFL, job->fd1_save);
		fcntl(job->fd2, F_SETFL, job->fd2_save);
		free(job);
		return -ENOSPC;
	}
	//将任务放入数组中
	job_list[pos] = job;
	pthread_mutex_unlock(&mut_job);
	//返回任务的下标
	return pos;
}


//取消任务
int rel_cancel_job(int jobid)
{
	if(jobid < 0)
		return -EINVAL;

	if(job_list[jobid]->state == STATE_CANCELED)
		return -EBUSY;

	job_list[jobid]->state = STATE_CANCELED;

	//成功取消任务返回0
	return 0;
}



//获取任务信息
int rel_getinfo_job(int jobid, rel_job_st* job)
{
	if(jobid < 0)
		return -EINVAL;

	job->state = job_list[jobid]->state;
	job->fd1 = job_list[jobid]->fd1;
	job->fd2 = job_list[jobid]->fd2;
	job->fd1_save = job_list[jobid]->fd1_save;
	job->fd2_save = job_list[jobid]->fd2_save;
	job->fsm12 = job_list[jobid]->fsm12;
	job->fsm21 = job_list[jobid]->fsm21;
	
	//成功返回0
	return 0;
}
