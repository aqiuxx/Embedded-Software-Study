#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
	char buf[100];
	char *name;
	char *head,*rear;
	int i,j;
	char mypwd[100];
	char *myarg[100];
	struct stat mystatbuf;
	while (1)
	{
		//Print the prompt
		//username@hostname:pathname[$/#] 
		gethostname(buf,100);
//		printf("%s",buf);
		name = getlogin();
//		printf("%s",name);
		getcwd(mypwd,100);
		printf("%s@%s:%s%c ",name,buf,mypwd,getuid()?'$':'#');
//		break;
		gets(buf);

		head = rear = buf;
//		printf("%d",*buf);
		i = 0;
#if 1
		while(*rear != '\n' && *rear != '\0')
		{
			while(*head == ' ' && *head != '\0')
			{
				head++;
			}
			rear = head;
			while(*rear != ' ' && *rear != '\0')
			{
				rear++;
			}
	//		printf("head:%p,rear:%p,%d,,,,%d,,,%d:%c\n",head,rear,rear - head,i,j,*head);
			myarg[i] = malloc(20);
			strncpy(myarg[i++],head,rear-head);
			myarg[i-1][rear-head] = 0;
//			printf("%s\n",myarg[i-1]);
//			meet a *,traver the dir
			if(!strcmp(myarg[i-1],"*"))
			{
				DIR *sdir = opendir(".");
				struct dirent *mydir;
				while(mydir = readdir(sdir))
				{
	//				printf("%s\n",mydir->d_name);
					if(mydir->d_name[0] == '.')
						continue;
					myarg[i] = malloc(20);
					myarg[i-1] = mydir->d_name;
					i++;
				}
			}
			head = rear;
		}
#endif
		if(0 == i)
			continue;
//		printf("%d\n",i);
		if (myarg[i-1][0] == 0)
			myarg[i-1] = NULL;
		else
			myarg[i] = NULL;




		if(!strcmp(myarg[0],"cd"))
		{
			if(myarg[1])
			{
//				printf("cd to :%s\n",myarg[1]);
				if(stat(myarg[1],&mystatbuf) < 0)
				{
					printf("mybash cd: %s: No such file or directory\n",myarg[1]);
					continue;
				}
				if(S_ISDIR(mystatbuf.st_mode))
					chdir(myarg[1]);
				else
				{
					printf("mybash: cd: %s is not a dirctory\n",myarg[1]);
				}
			}
			else
			{
//				printf("cd to home\n");
				chdir("/home/linux");
			}
			continue;
		}

//		achieve  >
		i = 0;
		while(myarg[i])
		{
			if(!strcmp(myarg[i],">"))
			{
				if(myarg[i+1])
					freopen(myarg[i+1],"w",stdout);
				else
				{
					printf("syntax error near unexpected token `newline'\n");					
				//	myarg[i] = NULL;
				//	break;
					goto nextstart;
				}
				while(myarg[i+2])
				{
					strcpy(myarg[i],myarg[i+2]);
					i++;
				}
				myarg[i] = NULL;
				break;

			}
			i++;
		}
//		printf("good\n");

		if ( 0 == fork() )
		{
			if ( execvp(myarg[0],myarg) < 0 )
			{
				printf("execve error\n");
			}
		}

		freopen("/dev/tty","w",stdout);
nextstart:
		wait(NULL);
	}
	return 0;
}
