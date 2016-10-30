#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <ctype.h>

//char *
int main(int argc, char *argv[])
{
	char *my_argv[10];
	my_argv[0] = "/bin/echo";
	my_argv[9] = NULL;

	while(1)
	{
		char *str;
		switch (argc){
			case 1:
				printf("NULL\n");
				break;
			case 2:
				if (*str == '$')
				{
					// 搜索环境变量是否有
					printf("search ENV \n");
					my_argv[1] = argv[1];
				}
				else
				{
					printf("%s\n",argv[1]);
				}

				break;

			default:
				if (isdigit(*argv[1]) )	//get one comand
				{
					int i = atoi(argv[1]);
					while(i--)
					{
						printf("%s\n", argv[2]);
					}
				}
		}



		//rintf("%s ", );

		fflush(stdout);

		char buf[100];
		gets(buf);


		int pid;
		if(0 == (pid = fork()))
		{


			execv("/bin/echo", my_argv);
		}

		wait(NULL); //等待前面代码执行，及时响应
	}
	return 0;
}