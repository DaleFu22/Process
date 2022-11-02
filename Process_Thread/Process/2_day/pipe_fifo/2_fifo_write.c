/*
 *有名管道，用于两个互不相关的进程间通信
 *该文件实现有名管道的写操作
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define QUIT "quit"
#define FILE_PATH "/tmp/myfifo.1"

int main(int argc,char *argv[])
{
	int fd = -1;
	char buf[BUFSIZ];
	/*1、若有名管道文件不存在则创建有名管道文件*/
#if 1
	if((fd = open(FILE_PATH,O_WRONLY)) < 0)//以只写方式打开失败，说明打开出错或文件不存在
	{
		if(mkfifo(FILE_PATH,0666) < 0)//假设open失败原因是文件不存在，则创建
		{
			perror("mkfifo");
			exit(1);
		}
		if( (fd = open(FILE_PATH,O_RDWR)) < 0)//若此时还打开失败，说明文件真的是打开失败出错
		{
			perror("open");
			exit(1);
		}
	}
#else
	if(access(FILE_PATH,F_OK) < 0)//检查文件是否存在
	{
		if(mkfifo(FILE_PATH,0666) < 0)//不存在就创建
		{
			perror("mkfifo");
			exit(1);
		}
	}
	fd = open(FILE_PATH,O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
#endif

	/*2、写操作*/
	while(1)
	{
		bzero(buf,BUFSIZ);
		fprintf(stderr,"Please input:");
		if(read(0,buf,BUFSIZ-1) < 0)
		{
			continue;
		}
		write(fd,buf,strlen(buf));
		if(!strncasecmp(buf,QUIT,strlen(QUIT)))
		{
			printf("Good bye..\n");
			break;
		}
	}
	close(fd);

	return 0;
}
