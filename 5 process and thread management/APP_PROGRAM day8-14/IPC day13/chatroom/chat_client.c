#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "msgfram.h"

#define WORKDIR "/home/linux/chatdir/"

NODE *onlinelist;
int fifofd;

void clienthand(NODE *onlinelist, MSGF *buf)
{
	if(LOGIN == buf->mdata.hdata.stat)
		insert_list(onlinelist, buf->mdata.hdata.usrname, -1);
	else
		delete_list(onlinelist, buf->mdata.hdata.usrname);

}

void *deamrutin(void *arg)
{

	MSGF buf = {0};
	while(1)
	{
		read(fifofd, &buf, sizeof buf);
		switch(buf.mtype)
		{
		case MHAND:
			clienthand(onlinelist, &buf);
			break;
		case MDATA:
			printf("%s: %s\n", buf.mdata.mdata.usrname_src, buf.mdata.mdata.data);
			break;
		}
	}
}

void strcpyname(char *name, char *buf)
{
	while(' '!= *buf)
		*name++ = *buf++;
	*name = '\0';
}


void strcpydata(char *data, char *buf)
{
	while(' '!= *buf++);

	while(*buf)
		*data++ = *buf++;
	*data = '\0';
}

void show_help(void)
{
	printf("***********************************************************\n");
	printf("*******.help  for help                  *******************\n");
	printf("*******.list  for show online mem       *******************\n");
	printf("*******.quit  for unlogin               *******************\n");
	printf("*******<name> <msgdata>                 *******************\n");
	printf("***********************************************************\n");
}

void do_unlogin(int serverfifofd, char *myname)
{
	MSGF buf = {0};
	buf.mtype = MHAND;
	strcpy(buf.mdata.hdata.usrname, myname);
	buf.mdata.hdata.stat = UNLOGIN;

	write(serverfifofd, &buf, sizeof buf);

	exit(0);
}

int main(int argc, char *argv[])
{
	if(2 != argc)
	{
		printf("Usage: %s <username>\n", argv[0]);
		return -1;
	}

	//create private fifo
	char fifoname[100] = {0};
	sprintf(fifoname, "%s%s%s", WORKDIR, argv[1], ".fifo");
	if(-1 == mkfifo(fifoname, 0666) )
	{
			if(EEXIST != errno)
			{
				perror("mkfifo ");
				exit(-1);
			}
	}
	
	int serverfifofd = open("/home/linux/chatdir/server.fifo", O_WRONLY);
	if(-1 == serverfifofd)
	{
		perror("open");
		exit(-1);
	}

	fifofd = open(fifoname, O_RDWR);
	if(-1 == fifofd)
	{
		perror("open");
		exit(-1);
	}

	//create online list
	onlinelist = create_list();

	//login
	MSGF buf = {0};
	buf.mtype = MHAND;
	strcpy(buf.mdata.hdata.usrname, argv[1]);
	buf.mdata.hdata.stat = LOGIN;
	
	write(serverfifofd, &buf, sizeof buf);
	printf("send hand !\n");
	//fead feedback
	pthread_t t;
	pthread_create(&t, NULL, deamrutin, NULL);

	char cmdline[100] = {0};
	while(1)
	{
		printf("chat> ");fflush(stdout);
		gets(cmdline);
		if(0 == strcmp(".help", cmdline))
		{
			show_help();
			continue;
		}
		else
		if(0 == strcmp(".quit", cmdline) )
		{
			do_unlogin(serverfifofd, argv[1]);
			continue;
		}
		else
		if(0 == strcmp(".list", cmdline) )
		{
			show_list(onlinelist);
			continue;
		}

		//chat
		MSGF chatbuf = {0};

		chatbuf.mtype = MDATA;
		strcpy(chatbuf.mdata.mdata.usrname_src, argv[1]);
		strcpyname(chatbuf.mdata.mdata.usrname_dest, cmdline);
		strcpydata(chatbuf.mdata.mdata.data, cmdline);

		write(serverfifofd, &chatbuf, sizeof chatbuf);
		
	}
}

