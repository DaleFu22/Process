#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
	int msgid;
	/*1、获取键值key*/
	key_t key = ftok("/tmp",2);
	printf("key = %x\n",key);

	/*2、创建或打开一个消息队列*/
	msgid = msgget(key,IPC_CREAT | 0664);
	if(msgid < 0)
	{
		perror("msgget");
		exit(1);
	}
	printf("msgid = %d\n",msgid);

	return 0;
}
