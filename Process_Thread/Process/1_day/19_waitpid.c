/*
 *产生一个僵尸进程，在本例中，son1将会变成僵尸进程，因为父进程没死，在waitpid等待子进程退出，但这里子进程son2退出后，waitpid就结束了
 *但此时son1在5秒后死亡，父进程无法收尸，一直在while(1);循环，所以导致son1变成僵尸进程。
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int  main(void)
{
	pid_t pid;
	if((pid = fork()) < 0)
	{
		perror("fork.\n");
	}
	else if(pid > 0)
	{
		printf("My pid = %d\n",getpid());
		if((pid = fork()) < 0)
		{
			perror("fork2.\n");
		}
		else if(pid > 0)
		{
			printf("I'm father.\n");
			printf("father pid = %d\n",getpid());
			waitpid(-1,NULL,0);
			//waitpid(-1,NULL,0);
			printf("1111111111111\n");
			while(1);
		}
		else
		{
			printf("son2 pid = %d\n",getpid());
			printf("son2 ppid = %d\n",getppid());
			sleep(2);
		}
	}
	else
	{
		printf("son1 pid = %d\n",getpid());
		printf("son1 ppid = %d\n",getppid());
		sleep(5);
	}

	return 0;
}
