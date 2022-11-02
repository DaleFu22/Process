/*
 *无名管道，用于具有亲缘关系的进程间通信
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define QUIT "quit"

int main(void)
{
	pid_t ret;
	char buf[BUFSIZ];
	int pipefd[2];
	printf("pipe demo\n");
	if(pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	ret = fork(); 
	switch(ret)
	{
		case -1:
			perror("fork");
			break;
		case 0://子进程用作写端
			{
				close(pipefd[0]);//子进程作写端时关闭读的文件描述符节省资源
				while(1)
				{
					fprintf(stderr,"Please input:");
					bzero(buf,BUFSIZ-1);
#if 1
					if(read(0,buf,BUFSIZ-1) < 0)
					{
						continue;
					}
#else
					if(fgets(buf,BUFSIZ-1,stdin) < 0)
					{
						continue;
					}
#endif
					if( !strncasecmp(buf,QUIT,strlen(QUIT)))
					{
						printf("It's quiting...\n");
						break;
					}
					write(pipefd[1],buf,strlen(buf));
				}
				close(pipefd[1]);
				exit(1);
			}
			break;
		default://父进程用作读端
			{
				int status;
				close(pipefd[1]);//父进程作读端时关闭写的文件描述符节省资源
				//usleep(100000);
				while(1)
				{
					if(!waitpid(ret,&status,WNOHANG))
					{
						bzero(buf,BUFSIZ);
						if(read(pipefd[0],buf,BUFSIZ-1) == 0)
						{
							printf("The write end if closed.\n");
							break;
						}
						printf("You said:%s\n",buf);
					}
				}
				close(pipefd[0]);
				exit(1);
			}
			break;
	}

	return 0;
}

