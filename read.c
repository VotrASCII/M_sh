#include<stdio.h>
#include<stdlib.h>
//#define BUFFER_SIZE 1024
//char *line;
char read_line()
{
	//int buf=BUFFER_SIZE;
	int pos=0;
	//char *buffer=malloc(sizeof(char)*buf);
	int c, i;
	char *line=NULL;
	ssize_t buf=0;
	getline(&line, &buf, stdin);
	//printf("%d \n", buf);
	return *line;
	/*
	if(!buffer)
	{
		printf("M_sh:ALLOCATION ERROR \n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		c=getchar();
		if(c==-1 || c=='\n')
		{
			buffer[pos]='\0';
			for(i=0; i<sizeof(buffer); i+=1)
			{
				printf("%d\n", buffer[i]);
			}
			//printf("%d \n", buffer[pos]);
			return *buffer;
		}
		else
		{
			buffer[pos]=c;
		}
		pos+=1;
		if(pos>=buf)
		{
			buf+=BUFFER_SIZE;
			buffer=realloc(buffer, buf);
			if(!buffer)
			{
				printf("M_sh:ALLOCATION ERROR \n");
				exit(EXIT_FAILURE);
			}
		}			
	}*/
	
}
void main()
{
	read_line();
	//printf("%s", line);
}	
