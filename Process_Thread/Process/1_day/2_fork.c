#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int a = 1;
int b;

int main(void)
{
	pid_t ret;
	static int c = 3;
	static int d;
	static int e = 5;
	ret = fork();
	a += 6;
	b += 6;
	c += 6;
	d += 6;
	e += 6;
	printf("a,b,c,d,e = %d,%d,%d,%d,%d\n",a,b,c,d,e);
	if(ret > 0)
	{
		sleep(1);
		printf("This is father process\n");
		printf("father pid = %d\n",getpid());
		printf("father's father pid = %d\n",getppid());
		printf("father:a,b,c,d,e = %d,%d,%d,%d,%d\n",a,b,c,d,e);
	}
	if(ret == 0)
	{
		a -= 5;
		c -= 5;
		e -= 5;
		printf("This is child process\n");
		printf("child pid = %d\n",getpid());
		printf("child's father pid = %d\n",getppid());
		printf("child:a,b,c,d,e = %d,%d,%d,%d,%d\n",a,b,c,d,e);
	}
	if(ret < 0)
	{
		perror("fork() error...\n");
		exit(1);
	}

	return 0;
}
