
#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct node{
	data_t data;
	struct node *next;
}linklist_t;

linklist_t * linklist_creat()
{
	linklist_t *h;
	h = (linklist_t *)malloc(sizeof(linklist_t));

	h->next = NULL;
	return h;
}

int linklist_insert(linklist_t *h, data_t value){
	linklist_t *tmp = (linklist_t *)malloc(sizeof(linklist_t));
	
	tmp->data = value;

	tmp->next = h->next;
	h->next = tmp;

	return 0;
}

int linklist_insert_tail(linklist_t *h, data_t value){
	linklist_t *tmp = (linklist_t *)malloc(sizeof(linklist_t));
	tmp->data  = value;
	
	while(h->next != NULL){
		h = h->next;
	}

	h->next = tmp;
	tmp->next = NULL;

	//h = tmp;

	return 0;
}



data_t linklist_delete_head(linklist_t *h){
	linklist_t *tmp;
	data_t value;

	tmp = h->next;
	value = tmp->data;

	h->next = tmp->next;

	free(tmp);
	tmp  = NULL;

	return value;
}

int linklist_delete_tail(linklist_t *h){
	while(h->next->next != NULL){
		h = h->next;
	}

	h->next = NULL;

	return 0;
}

int linklist_delete(linklist_t *h, data_t value){
	linklist_t *p;
	p = h;
	while(p->next != NULL){
		p = p->next;
		if(p->data == value){
		
		}
	}

	return 0;
}

int linklist_show(linklist_t *h){
	while(h->next != NULL){
		h = h->next;
		printf("%d \n", h->data);
	}

	return 0;
}



int linklist_change_data(linklist_t *h, data_t old_value, data_t new_value){

	while(h->next != NULL){
		h = h->next;
		if(h->data == old_value){
			h->data = new_value;
			return 0;
		}
	}
	
	printf("error!\n");
	return -1;
}
int linklist_change(linklist_t *h, int index, data_t value){
	int i = 0;

	while(h->next != NULL){
		h = h->next;
		if(i == index){
			h->data = value;
			return 0;
		}
		i++;
	}
	
	printf("error!\n");
	return -1;
}

int linklist_search(linklist_t *h, data_t value){
	int i = 0;

	while(h->next != NULL){
		h = h->next;
		if(h->data == value){
			return i;
		}
		i++;
	}
	
	printf("error!\n");
	return -1;
}


data_t linklist_search_Kdate(linklist_t *h, int k){
	linklist_t *pre,*post;
	data_t value;

	pre = h;
	post = h;
	int i = 1;

	while(i < k){
		post = post->next;
		i++;
	}
	
	//if( i != k){
	//	printf("index is out of range!");			
	//	return -1;
	//}

	while(post->next != NULL){
		pre = pre->next;
		post = post->next;
	}

	value = pre->data;

	return value;
}

int main(int argc, const char *argv[])
{
	linklist_t *h = linklist_creat();
	
	printf("insert head\n");
	linklist_insert(h, 10);
	linklist_insert(h, 20);
	linklist_insert(h, 30);
	linklist_insert(h, 40);
	linklist_insert(h, 50);

	linklist_show(h);

	printf("insert tail\n");
	linklist_insert_tail(h,100);
	linklist_show(h);

	printf("delete tail\n");
	linklist_delete_tail(h);
	linklist_show(h);


	printf("delete head\n");
	printf("%d \n",linklist_delete_head(h));

	printf("show\n");
	linklist_show(h);	
	
	printf("change data using old data\n");
	linklist_change_data(h,40,400);
	linklist_show(h);

	printf("change data using index\n");
	linklist_change(h,1,1);
	linklist_show(h);


	printf("search data\n");
	printf("%d\n",linklist_search(h,20));
	linklist_show(h);

	printf("search	k data\n");
	printf("Kdata = %d\n",linklist_search_Kdate(h,1));
	printf("Kdata = %d\n",linklist_search_Kdate(h,10));
	linklist_show(h);

	return 0;
}
