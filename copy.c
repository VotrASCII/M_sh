#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
//#define BUF 100
int main(int argc, char **argv)
{
	int fd1, fd2, BUF;
	//char buffer[BUF];
	struct stat fs;
	if (argc>2)
	{
		if ((fd1=open(argv[1], O_RDONLY))==-1)
		{
			perror("open");
			return -1;
		}
		fstat(fd1, &fs);
		BUF=fs.st_size;
		char buffer[BUF];
		if ((fd2=open(argv[2], O_RDWR|O_APPEND|O_CREAT|O_EXCL, S_IRWXU|S_IRWXG))==-1)
		{
			perror("open");
			return -1;
		}
		while(read(fd1, buffer, sizeof(buffer))>0)
		{
			write(fd2, buffer, sizeof(buffer));
		}		
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	close(fd1);
	close(fd2);
	return 0;
}
