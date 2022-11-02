#include <stdio.h>
#include <stdlib.h>

void fun1(void)
{
	printf("1:fun1\n");
}

void fun2(void)
{
	printf("2:fun2\n");
}

void fun3(void)
{
	printf("3:fun3\n");
}

int main(void)
{
	printf("atexit() demo\n");

	atexit(fun1);
	atexit(fun2);
	atexit(fun3);

	exit(0);
}
