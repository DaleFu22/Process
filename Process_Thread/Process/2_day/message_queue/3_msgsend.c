#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf{
	long mtype;
	char mtext[20];
	int number;
};

int main(void)
{
	int msgid;
	struct msqid_ds msg_info;
	struct msgbuf msg_buf = {10,"Dale",666};
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

	/*3、对一条消息队列进行控制*/
	if(msgctl(msgid,IPC_STAT,&msg_info) < 0)
	{
		perror("msgctl");
		exit(1);
	}
	//获取消息队列的相关信息
	printf("msg_info.__msg_cbytes = %ld\n",msg_info.__msg_cbytes);
	printf("msg_info.msg_qbytes = %ld\n",msg_info.msg_qbytes);

	//删除消息队列
//	msgctl(msgid,IPC_RMID,NULL);

	/*4、向消息队列发送消息*/
	if(msgsnd(msgid,(void *)&msg_buf,sizeof(msg_buf) - sizeof(msg_buf.mtype),0) < 0)
	{
		perror("msgsnd");
		exit(1);
	}

	return 0;
}
