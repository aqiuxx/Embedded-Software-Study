#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main()
{
	DIR *dp = opendir(".");

	struct dirent *p;

	struct stat s;

	struct passwd *pwd;
	struct group *grd;

	time_t t;
	struct tm *tt;

	char filetype;
	char *owenerpermision;
	char *grouppermision;
	char *otherpermision;


	while( p = readdir(dp) )
	{
//		printf("%s\n", p->d_name);
		stat(p->d_name, &s);

		// filetype
		switch(s.st_mode & S_IFMT)
		{
			case S_IFBLK:  /*printf("block device\n");*/    		filetype ='b';        break;
			case S_IFCHR:  /*printf("character device\n");*/        filetype ='c';        break;
			case S_IFDIR:  /*printf("directory\n");*/               filetype ='d';        break;
			case S_IFIFO:  /*printf("FIFO/pipe\n");*/               filetype ='p';        break;
			case S_IFLNK:  /*printf("symlink\n"); */                filetype ='l';        break;
			case S_IFREG:  /*printf("regular file\n"); */           filetype ='-';        break;
			case S_IFSOCK: /*printf("socket\n");   */               filetype ='s';        break;
			default:       /*printf("unknown?\n"); */               filetype =' ';        break;
		}

		// owner permision
		switch(s.st_mode & S_IRWXU)
		{
			case (S_IRUSR | S_IWUSR | S_IXUSR):             owenerpermision ="rwx";        break;
			case (S_IRUSR | S_IWUSR 	     ):      		owenerpermision ="rw-";        break;
			case (S_IRUSR 		    | S_IXUSR):     	    owenerpermision ="r-x";        break;
			case (S_IRUSR 					 ):  	    	owenerpermision ="r--";        break;
			case ( 		    S_IWUSR | S_IXUSR):             owenerpermision ="-wx";        break;
			case (			S_IWUSR 		 ):     	 	owenerpermision ="-w-";        break;
			case (					  S_IXUSR):       	    owenerpermision ="--x";        break;
			default:    								    owenerpermision ="   ";        break;
		}

		// user permision
		switch(s.st_mode & S_IRWXG)
		{
			case (S_IRGRP | S_IWGRP | S_IXGRP):             grouppermision ="rwx";        break;
			case (S_IRGRP | S_IWGRP 	     ):      		grouppermision ="rw-";        break;
			case (S_IRGRP 		    | S_IXGRP):      	    grouppermision ="r-x";        break;
			case (S_IRGRP 					 ):     	 	grouppermision ="r--";        break;
			case ( 		    S_IWGRP | S_IXGRP):             grouppermision ="-wx";        break;
			case (			S_IWGRP 		 ):      	 	grouppermision ="-w-";        break;
			case (					  S_IXGRP):       	    grouppermision ="--x";        break;
			default:   							   			grouppermision ="   ";        break;
		}

		// user permision
		switch(s.st_mode & S_IRWXG)
		{
			case (S_IROTH | S_IWOTH | S_IXOTH):             otherpermision ="rwx";        break;
			case (S_IROTH | S_IWOTH 	     ):     		otherpermision ="rw-";        break;
			case (S_IROTH 		    | S_IXOTH):      	    otherpermision ="r-x";        break;
			case (S_IROTH 					 ):     	 	otherpermision ="r--";        break;
			case ( 		    S_IWOTH | S_IXOTH):             otherpermision ="-wx";        break;
			case (			S_IWOTH 		 ):     	 	otherpermision ="-w-";        break;
			case (					  S_IXOTH):       	    otherpermision ="--x";        break;
			default:   						    			otherpermision ="   ";        break;
		}

		pwd = getpwuid(s.st_uid);
		grd = getgrgid(s.st_gid);

		t = s.st_atime;
		tt = localtime(&t);


		printf( "%c%s%s%s  %d   %s   %s    %4ld    %02d  %02d   %02d:%02d:%02d  \033[1;31;40m %s  \033[0m\n",
			filetype, owenerpermision, grouppermision, otherpermision,
			s.st_nlink,
			pwd->pw_name,
			grd->gr_name,
			s.st_size,
			tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec,
			 p->d_name );
	}
}
