#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main()
{
	if(0 < fork() ) //��һ���������ӽ��̣��˳�������
		exit(0);

	setsid(); //�ڶ����������»Ự������ԭ�Ự��ԭ�����顢ԭ�����նˣ�

	chdir("/"); // �������� �ı䵱ǰĿ¼

	umask(0); //�����ļ�Ȩ������

	int maxfd = getdtablesize();  //�ر��ļ�������
	while(maxfd--)
		close(maxfd);

	open

	while(1)
	{
		syslog(LOG_INFO, "hello %d\n", 250); //syslog ��Linux�е�ϵͳ��־�������
		sleep(1);
	}
}
