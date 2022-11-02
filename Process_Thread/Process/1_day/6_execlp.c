#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int a = 1;
int b;

int main(void)
{
	pid_t ret;
	printf("fork()+execl() demo.\n");
	
	ret = fork();

	switch(ret)
	{
		case -1:
			perror("fork() failed...\n");
			break;
		case 0:
		{
			printf("child process...\n");
			/*第一个参数"ls"是文件名，系统会去环境变量$PATH路径下寻找这个文件
			 *第二个参数"ls"是执行参数。
			 */
			execlp("ls","ls","-al",NULL);
			printf("can I be work?\n");
		}
		break;
		default:
		{
			sleep(1);
			printf("Father Process\n");
		}
		break;
	}

	return 0;
}
