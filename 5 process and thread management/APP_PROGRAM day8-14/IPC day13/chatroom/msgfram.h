#ifndef _MF_
#define _MF_

#define LOGIN 110
#define UNLOGIN 111
struct handdata{
	char usrname[20];
	int stat;
};

struct msgdata{
	char usrname_src[20];
	char usrname_dest[20];//xxx for broadcast
	char data[100];
};

typedef enum{MHAND, MDATA }msgfram_t;
typedef struct msgfram{
	msgfram_t mtype;
	union{
		struct handdata hdata;
		struct msgdata mdata;
	}mdata;
}MSGF;

#endif
