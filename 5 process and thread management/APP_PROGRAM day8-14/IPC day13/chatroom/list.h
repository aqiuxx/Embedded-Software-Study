#ifndef _LIST_
#define _LIST_

#define NAME_SIZE 20
typedef struct node{
	char usrname[NAME_SIZE];
	int usrfd;

	struct node *next;
}NODE;

NODE *create_list(void);

int insert_list(NODE *head, const char *usrname, int downfd);

int delete_list(NODE *head, const char *usrname);

NODE *find_list(NODE *head, const char *usrname);

void show_list(NODE *head);

#endif
