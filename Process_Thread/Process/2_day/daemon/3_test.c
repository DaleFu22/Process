/*
 *创建一个守护进程
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int i;
	pid_t pid;
	//1、初步摆脱终端，创建子进程，让父进程结束
	if((pid = fork()) < 0)
	{
		perror("fork() no.1");
		exit(1);
	}
	else if(pid > 0)
	{
		//让父进程直接结束
		exit(0);
	}

	//2、让子进程成为新会话组组长和进程组组长
	if(setsid() < 0)
	{
		perror("setsid()");
		exit(1);
	}

	//3、为防止该进程可能开终端，在该进程下创建一个子进程，并结束该进程
	if((pid = fork()) < 0)
	{
		perror("fork() no.2");
		exit(1);
	}
	else if(pid > 0)
	{
		//结束该进程
		exit(1);
	}

	//4、改变掩码，增加守护进程的灵活性，让文件权限达到最高
	umask(0);

	//5、 为了守护进程的工作不随意的可以被改变，改变守护进程的工作目录
	if(chdir("/tmp") < 0)
	{
		perror("chdir()");
		exit(1);
	}
	
	//6、关闭从父进程那里继承的文件描述符
	for(i = 0;i < sysconf(_SC_OPEN_MAX);i++)
	{
		close(i);
	}

	//7、因为 0 1 2 三个文件描述符比较特殊,先占用这个三个文件描述
	open("dev/null",O_RDWR);
	dup(0);
	dup(0);


	return 0;
}
