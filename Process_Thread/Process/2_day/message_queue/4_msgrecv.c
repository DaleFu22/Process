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
	struct msgbuf msg_buf;
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

	/*4、从消息队列接收消息*/
#if 1
	if(msgrcv(msgid,(void *)&msg_buf,sizeof(msg_buf) - sizeof(msg_buf.mtype),10,0) < 0)
	{
		perror("msgsnd");
		exit(1);
	}
#else
	//若尝试从一个消息类型mtype=6的消息节点（消息队列中无此消息类型）获取数据，将获取不到并会造成阻塞
	if(msgrcv(msgid,(void *)&msg_buf,sizeof(msg_buf) - sizeof(msg_buf.mtype),6,0) < 0)
	{
		perror("msgsnd");
		exit(1);
	}
#endif
	printf("Received:msg_buf.mtext = %s\n",msg_buf.mtext);
	printf("Received:msg_buf.number = %d\n",msg_buf.number);

	return 0;
}
