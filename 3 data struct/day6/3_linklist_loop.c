#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct dnode_t{
	data_t data;
	struct dnode_t *before;
	struct dnode_t *next;
}dlinklist_t;

dlinklist_t * dlinklist_create(){
	dlinklist_t* h;
	h = (dlinklist_t *)malloc(sizeof(dlinklist_t));
	h->data = 1000000;
	
	h->next = h;
	h->before = h;

	return h;
}


int dlinklist_insert_head( dlinklist_t *h, data_t value ){
	dlinklist_t *tmp = (dlinklist_t *)malloc(sizeof(dlinklist_t));

	tmp->data = value;

	tmp->next = h->next;
	h->next->before = tmp;
	
	h->next = tmp;
	tmp->before = h;
	
	return 0;
}

dlinklist_t * dlinklist_delete_head( dlinklist_t *h ){
	
	dlinklist_t *tmp;
	tmp = h->next;

	h->next->before = h->before;
	h->before->next = h->next;
	
	free(h);
	h = NULL;

	return tmp;
}


int dlinklist_show( dlinklist_t *h ){
	
	dlinklist_t *tmp = h;
	while(h->next != tmp){
		h = h->next;
		printf("%d \n", h->data);
	}

	printf("\n");

	return 0;
}

int dlinklist_show_nohead( dlinklist_t *h ){
	
	dlinklist_t *tmp = h;
	int i =0;
	//while(i<15){
	while(h->next != tmp){
		printf("%d \n", h->data);
		h = h->next;
		i++;
	}

	printf("%d \n", h->data);

	return 0;
}

int main(int argc, const char *argv[])
{
	dlinklist_t *h;
	h = dlinklist_create();

	printf("dlinklist_insert_head\n");
	dlinklist_insert_head(h, 10);
	dlinklist_insert_head(h, 20);
	dlinklist_insert_head(h, 30);
	dlinklist_insert_head(h, 40);
	dlinklist_show(h);

	printf("dlinklist_delete_head\n");
	h = dlinklist_delete_head(h);
	dlinklist_show(h);
	dlinklist_show_nohead(h);
	return 0;
}
