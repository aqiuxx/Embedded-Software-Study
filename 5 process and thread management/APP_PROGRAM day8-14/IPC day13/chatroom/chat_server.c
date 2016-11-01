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

void servehand(MSGF *mbuf, NODE *onlinelist)
{
	if(LOGIN == mbuf->mdata.hdata.stat)
	{
		//get user fifo connect
		char fifoname[100] = {0};
		sprintf(fifoname, "%s%s%s", WORKDIR, mbuf->mdata.hdata.usrname, ".fifo");
		int userfd = open(fifoname, O_WRONLY);
		if(-1 == userfd)
		{
			perror("open user fifo");
			return;
		}

		NODE *thead = onlinelist;
		//broadcast
		while(thead->next)
		{
			write(thead->next->usrfd, mbuf, sizeof(MSGF));
			thead = thead->next;
		}
		//feedback
		thead = onlinelist;
		MSGF buf = {.mtype = MHAND};
		buf.mdata.hdata.stat = LOGIN;
		
		while(thead->next)
		{
			strcpy(buf.mdata.hdata.usrname, thead->next->usrname);
			write(userfd, &buf, sizeof(MSGF));
			thead = thead->next;
		}

		//recode
		insert_list(onlinelist, mbuf->mdata.hdata.usrname, userfd);
	}
	else
	if(UNLOGIN == mbuf->mdata.hdata.stat)
	{
		delete_list(onlinelist, mbuf->mdata.hdata.usrname);

		MSGF buf = {.mtype = MHAND};
		buf.mdata.hdata.stat = UNLOGIN;
		strcpy(buf.mdata.hdata.usrname, mbuf->mdata.hdata.usrname);
		
		NODE *thead = onlinelist;
		while(thead->next)
		{
			write(thead->next->usrfd, &buf, sizeof(MSGF));
			thead = thead->next;
		}
	}
}

void servedata(MSGF *mbuf, NODE *onlinelist)
{
	//route
		NODE *thead = onlinelist;
		while(thead->next)
		{
			if(0 == strcmp("xxx", mbuf->mdata.mdata.usrname_dest) 
						|| 
			0 == strcmp(mbuf->mdata.mdata.usrname_dest, thead->next->usrname) 
			)
				write(thead->next->usrfd, mbuf, sizeof(MSGF));
			thead = thead->next;
		}
}

int main()
{
	//create serverfifo
	if(-1 == mkfifo("/home/linux/chatdir/server.fifo", 0666) )
	{
		if(EEXIST != errno)
		{
			perror("mkfifo ");
			exit(-1);
		}
	}
	//create online list
	NODE *onlinelist = create_list();
	//serve
	int serverfifofd = open("/home/linux/chatdir/server.fifo", O_RDONLY);
	if(-1 == serverfifofd)
	{
		perror("open");
		exit(-1);
	}

	MSGF msgbuf;
	while(1)
	{
		int n = read(serverfifofd, &msgbuf, sizeof msgbuf);
		printf("read %d: %d\n", n, msgbuf.mtype);
		switch(msgbuf.mtype)
		{
		case MHAND:
			servehand(&msgbuf, onlinelist);
			break;
		case MDATA:
			servedata(&msgbuf, onlinelist);
			break;
		default:
			printf("unkown protocol!\n");
			break;
		}

	}
}

