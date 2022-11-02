#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t ret;
	ret = fork();
	if(ret > 0)
	{
		printf("This is father process\n");
		printf("father pid = %d\n",getpid());
		printf("father's father pid = %d\n",getppid());
	}
	if(ret == 0)
	{
		printf("This is child process\n");
		printf("child pid = %d\n",getpid());
		printf("child's father pid = %d\n",getppid());
	}

	return 0;
}
