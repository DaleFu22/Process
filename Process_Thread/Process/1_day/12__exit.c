#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("exit() demo\n");

	printf("演示_exit()不会清IO缓冲");
	_exit(0);

}
