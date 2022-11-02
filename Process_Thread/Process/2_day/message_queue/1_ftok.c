#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(void)
{
	key_t key = ftok("./222",2);
	printf("key = %d\n",key);

	return 0;
}
