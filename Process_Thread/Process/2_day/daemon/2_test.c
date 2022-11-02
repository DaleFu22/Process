#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	if((pid = fork()) < 0)
	{
		perror("fork");
	}
	else if(pid > 0)
	{
		while(1);
	}

	//子进程循环打印
	while(1)
	{
		printf("son\n");
		sleep(1);
	}

	return 0;
}
