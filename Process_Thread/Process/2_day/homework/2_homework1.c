/*
 *用进程相关API函数编程一个程序，使之产生一个进程扇：父进程产生一系列子进程，每个子进程打印自己的PID然后退出。要求父进程最后打印PID。
 *该代码大致流程，父进程先fork()，然后开始wait循环等待，子进程开始循环打印，打印的顺序是不确定的，因为子进程的执行顺序不确定
 *修改成增序版本:加一个sleep()函数
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int i;
	pid_t pid;
	for(i = 0;i < 10;i++)
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork()");
			exit(1);
		}
		if(pid == 0)
		{
			printf("child%d = %d\n",i,getpid());
			//printf("ppid = %d\n",getppid());
			exit(1);
		}
		sleep(1);
	}

	for(i = 0;i < 10;i++)
	{
		wait(NULL);
	}
	printf("father pid = %d\n",getpid());

	return 0;
}
