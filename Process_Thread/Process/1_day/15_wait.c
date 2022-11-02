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
			int status;
			wait(&status);
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
