#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	pid_t ret;
	printf("fork()+wait() demo.\n");
	
	ret = fork();

	switch(ret)
	{
		case -1:
			perror("fork() failed...\n");
			break;
		case 0:
		{
			printf("child process...\n");
			sleep(1);
			return 3;
			//return 108;
		}
		break;
		default:
		{
			printf("Father Process\n");
			int status,n;
			//wait(&status);
			//waitpid(-1,&status,0);//阻塞等待任意子进程退出
			//waitpid(ret,&status,0);//阻塞等待指定pid = ret的子进程退出
			while(!(n = waitpid(ret,&status,WNOHANG)))//非阻塞，当无子进程退出时返回值是0
			{
				printf("n = %d\n",n);
				usleep(200000);//睡眠200ms
			}
			printf("status = %d\t,right shit 8 bit = %d\n",status,status>>8);
			printf("The child process exit value = %d\n",WEXITSTATUS(status));
			if(WIFEXITED(status))
			{
				printf("The child process terminated normally.\n");
			}
			if(WIFSIGNALED(status))
			{
				printf("The child process was terminated by a signal.\n");
			}
		}
		break;
	}

	return 0;
}
