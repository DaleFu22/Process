/*
 *有名管道，用于两个互不相关的进程间通信
 *该文件实现有名管道的读操作
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
#include <errno.h>

#define FILE_PATH "/tmp/myfifo.1"
#define QUIT "quit"

int main(int argc,char *argv[])
{
	int fd = -1,ret = -1;
	char buf[BUFSIZ];
	/*1、既然是读操作那么就默认要求有名管道文件已经存在，否则就退出*/
	if(access(FILE_PATH,F_OK) < 0)//判断文件是否存在，不存在就退出
	{
		printf("The file is not exist.\n");
		exit(1);
	}

	/*2、以读方式打开文件*/
	fd = open(FILE_PATH,O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}

	/*3、读操作*/
	while(1)
	{
		fprintf(stderr,"You said:");
		bzero(buf,BUFSIZ);
		do{
			ret = read(fd,buf,BUFSIZ-1);
		}while(ret < 0 && EINTR == errno);
		if(ret < 0)
		{
			continue;
		}
		if(!strncasecmp(buf,QUIT,strlen(QUIT)))
		{
			printf("The write process has existed.\n");
			break;
		}	
		printf("%s\n",buf);
	}

	return 0;
}
