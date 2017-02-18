#include<stdio.h>
#include<utime.h>
#include<sys/time.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char** argv)
{
	char buf[1];
	int i, fd1;
	if(argc>1)
	{
		for(i=1; i<argc; i++)
		{
			struct utimbuf *t = NULL;
			struct stat statbuf;
			stat(argv[i], &statbuf);
			fd1=open(argv[i], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
			utime(argv[i],t);
			close(fd1);
		}
	}
	else
	{
		printf("Touch expects atleast one arg");
		exit(EXIT_FAILURE);
	}
}

