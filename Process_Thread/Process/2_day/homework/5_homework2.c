/*
 *用进程相关API函数编写一个程序，使之产生一个进程链，子进程再创建子进程，然后往复创建。
 *实现一个子进程要比父进程先打印PID的版本。（即打印的PID一般是递减的）
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
		}
		else if(pid > 0)
		{
			wait(NULL);
			//sleep(1);
			printf("pid = %d\n",getpid());
			exit(0);
		}
	}

	return 0;
}
