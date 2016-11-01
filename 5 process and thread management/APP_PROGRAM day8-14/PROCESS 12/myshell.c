#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <linux/limits.h>
#include <i386-linux-gnu/bits/local_lim.h>

void changestyle(char *argv[], char buf[100])
{
	buf++;
	while(*buf)
	{
		if(' '==*(buf-1) && ' '!=*buf)
		{
			*argv++ = buf;
			*(buf-1) = '\0';
		}

		buf++;
	}
}

int main()
{
	while(1)
	{
		char pwdpath[PATH_MAX] = {0};
		getcwd(pwdpath, PATH_MAX);
		char hostname[HOST_NAME_MAX] = {0};
		gethostname(hostname, HOST_NAME_MAX);

		printf("%s@%s:%s%c ", getpwuid(getuid())->pw_name, hostname, pwdpath, getuid()?'$':'#'); fflush(stdout);

		char buf[100] = {' '};
		gets(buf+1);
	
		if(0 == strncmp("cd", buf+1, 2))
		{
			chdir(buf+4);
			continue;
		}
		
	
		int pid;
		if(0 == (pid = fork()))
		{

			//buf----->argv
			char *argv[100] = {NULL};

			changestyle(argv, buf);

			execvp(argv[0], argv);

#if 0
			buf //????
			execl("/bin/ls", "/bin/ls", NULL);
#endif
		}

		wait(NULL);	
//		printf("unkown cmd !\n");
	}
}
