#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//isCommandExisted(*myargv);

int main(int argc, char *argv[])
{
	char *my_argv[10];

	char seps[]   = " ,\t\n";
	char *token;
	int ret;

	while(1)
	{
		int i = 0;
		char pwdpath[100] = {0};

		getcwd(pwdpath, 100);

		char hostname[100];			//此处不能定义为char *hostname, 用于接收字符串;
		char *username;				//此处是接受一个返回的地址
		gethostname(hostname, 20);
		username = getlogin();

		printf("%s@%s:%s%c ",username ,hostname , pwdpath, getuid()?'$':'#'); fflush(stdout);


		char buf[100];
		gets(buf);

		/**
		 * 将命令行参数 存储到 my_argv 指针数组
		 */
		token = strtok( buf, seps );
		while( token != NULL )
		{
		  /* While there are tokens in "buf" */
		  //printf( "%s\n", token );

		  /* Get next token: */
		  my_argv[i] = token;
		  i++;
		  token = strtok( NULL, seps );
		}

		my_argv[i] = NULL; //必须的有


		/**
		 * *************************************************
		 * “cd” 实现
		 * *************************************************
		 */
		int fd;
		if ( !(ret = strcmp(my_argv[0],"cd")) )
		{
			if((fd = open(my_argv[1], O_RDONLY)) < 0)
            {
                printf("open Error: command not found!\n");
                //exit(1);
            }

            if(fchdir(fd) < 0)   //调用fchdir实现目录间的切换
            {
                printf("cd command error!\n");
                //exit();
            }
		}

		/**
		 * “ls＊” 实现
		 */



		/**
		 * “execvp” 实现
		 */
		int pid;
		if(0 == (pid = fork()))
		{
		/**
		 * “ls＊” 实现
		 */

		/*if(!isCommandExisted(my_argv[0]))
        {
            printf("%s : command not found\n", my_argv[0]);
            exit(0);
        }*/

    	int oldfd;
    	char *file;

        for(i = 0; my_argv[i] != NULL; i++)
        {
            if(!strcmp(my_argv[i], ">"))
            {
                file = my_argv[i+1];
                my_argv[i] = NULL;
            }
        }

        if((oldfd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
        {
            printf("open file error  ??\n");
            //exit(-1);
        }

        dup2(oldfd, 1);

		execvp(my_argv[0], my_argv);

#if 0
		//buf //????
		//execl("/bin/ls", "/bin/ls", NULL);
#endif
		}

		wait(NULL); //等待前面代码执行，及时响应
	}
}

