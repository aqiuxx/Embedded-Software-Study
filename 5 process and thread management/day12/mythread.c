#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>

typedef struct thread_info1{
	int len;
	char *p;
}thread_info;

char *rev_buf(const char *buf, int len)
{
		static char rbuf[100];

		while(len--)
			rbuf[len] = *buf++;
		
		return rbuf;
}


void print_buf(const char *buf)
{
//		while(len--)
		printf("%s", buf);
}


void *func1(void *arg)
{
		thread_info *tinfo = (thread_info *) arg;
		char *rbuf = rev_buf(tinfo->p, tinfo->len);
		while(1)
			printf("[%lu] %s\n", pthread_self(), rbuf);
}

void *func2(void *arg)
{
		thread_info *tinfo = (thread_info *) arg;
		print_buf(tinfo->p);
		while(1)
			printf("[%lu] %s\n", pthread_self(), tinfo->p);
}



int main(int argc, const char *argv[])
{


	thread_info *buf_info = malloc(sizeof(thread_info));
	char buff[] = "abcde";
	buf_info->len = 5;
	buf_info->p = buff; 
	
	//create two thread, receive arg
	pthread_t t1,t2;
		
	printf("11111111i1\n");
	pthread_create(&t1, NULL, &func1, buf_info);
	pthread_create(&t2, NULL, &func2, buf_info);
	//revers_func

	pause();
	//print_func


	return 0;
}

