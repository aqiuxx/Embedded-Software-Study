#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main()
{
	if(0 < fork() ) //第一步，创建子进程，退出父进程
		exit(0);

	setsid(); //第二步，创建新会话（脱离原会话、原进程组、原控制终端）

	chdir("/"); // 第三步， 改变当前目录

	umask(0); //重设文件权限掩码

	int maxfd = getdtablesize();  //关闭文件描述符
	while(maxfd--)
		close(maxfd);

	open

	while(1)
	{
		syslog(LOG_INFO, "hello %d\n", 250); //syslog 是Linux中的系统日志管理服务
		sleep(1);
	}
}
