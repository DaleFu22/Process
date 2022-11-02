/*
 *使用守护进程做点事儿
 *实现在/tmp目录下创建一个time.txt文件实现时间的打印，每隔一秒打印一次
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <syslog.h>

void FuWL_init()
{
	int i;
	pid_t pid;
	//1、初步摆脱终端，创建子进程，让父进程结束
	if((pid = fork()) < 0)
	{
		perror("fork() no.1");
		exit(1);
	}
	else if(pid > 0)
	{
		//让父进程直接结束
		exit(0);
	}

	//2、让子进程成为新会话组组长和进程组组长
	if(setsid() < 0)
	{
		perror("setsid()");
		exit(1);
	}

	//3、为防止该进程可能开终端，在该进程下创建一个子进程，并结束该进程
	if((pid = fork()) < 0)
	{
		perror("fork() no.2");
		exit(1);
	}
	else if(pid > 0)
	{
		//结束该进程
		exit(1);
	}

	//4、改变掩码，增加守护进程的灵活性，让文件权限达到最高
	umask(0);

	//5、 为了守护进程的工作不随意的可以被改变，改变守护进程的工作目录
	if(chdir("/tmp") < 0)
	{
		perror("chdir()");
		exit(1);
	}
	
	//6、关闭从父进程那里继承的文件描述符
	for(i = 0;i < sysconf(_SC_OPEN_MAX);i++)
	{
		close(i);
	}

	//7、因为 0 1 2 三个文件描述符比较特殊,先占用这个三个文件描述
	open("dev/null",O_RDWR);
	dup(0);
	dup(0);

}

void Usage(char *s)
{
	printf("Usage:\n");
	printf("\t%s <dst_file>\n",s);
	printf("\t<dst_file>:the destination file of the open.\n");
}

int main(int argc,char *argv[])
{
	int fd = -1;
	time_t cur_sec;
	struct tm *tm;
	char buf[BUFSIZ];
	bzero(buf,BUFSIZ);
	if(argc != 2)
	{
		Usage(argv[0]);
		exit(1);
	}
	FuWL_init();

	//日志调试
	openlog("FuWeiLiang",LOG_PID,LOG_DAEMON);
	fd = open(argv[1],O_RDWR | O_CREAT | O_EXCL | O_TRUNC,0666);
	if(fd < 0 && EEXIST == errno)
	{
		fd = open(argv[1],O_RDWR);
		if(fd < 0)
		{
			//perror("open failed");
			//perror替换成日志调试syslog()
			syslog(LOG_ERR,"open:%s\n",strerror(errno));
			exit(1);
		}
	}
	//随便打印一些什么日志调试信息
	syslog(LOG_INFO,"Hello World");
	while(1)
	{
		cur_sec = time(NULL);
		tm = localtime(&cur_sec);
		snprintf(buf,BUFSIZ-1,"%d %d %d %d:%d:%d\n",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
		write(fd,buf,strlen(buf));
		fsync(fd);
		sleep(1);
	}

	closelog();
	close(fd);
	return 0;
}
