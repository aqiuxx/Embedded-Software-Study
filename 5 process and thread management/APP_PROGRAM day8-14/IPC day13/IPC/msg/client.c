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
	if(2 != argc)
	{
		printf("Usage: %s <type> \n", argv[0]);
		return -1;
	}
		
	int msgid = msgget(888, 0666);
	if(-1 == msgid)
	{
		perror("msgid");
		return -1;
	}

	MSG buf;

	msgrcv(msgid, &buf, SIZE, atoi(argv[1]), 0);

	printf("recv: %s\n", buf.data);
}
