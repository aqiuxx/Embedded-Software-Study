#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define SIZE 100

typedef struct {
	long mtype;
	char data[SIZE];
}MSG;

int main(int argc, char *argv[])
{
	if(3 != argc)
	{
		printf("Usage: %s <type> <data>\n", argv[0]);
		return -1;
	}
		
	int msgid = msgget(888, 0666 | IPC_CREAT);
	if(-1 == msgid)
	{
		perror("msgid");
		return -1;
	}

	MSG buf;
	buf.mtype = atoi(argv[1]);
	strcpy(buf.data, argv[2]);

	msgsnd(msgid, &buf, SIZE, 0);
}
