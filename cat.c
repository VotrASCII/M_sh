#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
//#define BUF 1024
int main(int argc,char** argv)
{
	struct stat fs;
	int fd1, BUF;
	//char buffer[BUF];
	if(argc!=2)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		if(access(argv[1],R_OK)==0)
		{
			int fd1=open(argv[1],O_RDONLY,S_IRUSR);
			fstat(fd1, &fs);
			BUF=fs.st_size;
			char buf[BUF];
			while(read(fd1, buf, sizeof(buf))>0)
			{
				printf("%s", buf);
			}
			close(fd1);
		}
	}
	return 0;
}
