#include <stdio.h>

int main(void)
{
#if 1
	int i = 0;
	while(1)
	{
		volatile int j,k;
		for(i = 0;i < 1000000;i++)
		{
			printf("hello %d\n",j++);
			printf("world %d\n",j++);
		}
	}
#else
	while(1)
	{
		printf("hello world\n");
	}
#endif
	return 0;
}
