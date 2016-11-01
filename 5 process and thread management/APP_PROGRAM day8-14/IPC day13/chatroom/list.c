#include "list.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>

NODE *create_list(void)
{
	NODE *head = malloc(sizeof(NODE));
	bzero(head, sizeof(NODE));

	return head;
}

int insert_list(NODE *head, const char *usrname, int usrfd)
{
	NODE *node = malloc(sizeof(NODE));
	bzero(node, sizeof(NODE));
	strcpy(node->usrname, usrname);
	node->usrfd = usrfd;

	node->next = head->next;
	head->next = node;
	
}

int delete_list(NODE *head, const char *usrname)
{
	while(head->next)
	{
		if(0 == strcmp(head->next->usrname, usrname) )
		{
			NODE *temnode = head->next;
			head->next = temnode->next;
			free(temnode);
		}
		head = head->next;
	}
}

NODE *find_list(NODE *head, const char *usrname)
{
	while(head->next)
	{
		if(0 == strcmp(head->next->usrname, usrname) )
			return head->next;

		head = head->next;
	}

	return NULL;
}

void show_list(NODE *head)
{
	while(head->next)
	{
		printf("%s[%d]\n", head->next->usrname, head->next->usrfd);
		head = head->next;
	}
}

