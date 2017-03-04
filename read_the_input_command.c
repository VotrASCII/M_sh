#include<stdio.h>
#include<stdlib.h>
#define BUFFER_SIZE 1024
//char *line = "\ndkjfskdg\n";
char *buffer;
char read_line()
{
	int buf=BUFFER_SIZE;
	int pos=0;
	buffer=malloc(sizeof(char)*buf); //returns NULL if 0 size allocated
	int c, i;
	//char *line=NULL;
	//ssize_t buf=0;
	//getline(&line, &buf, stdin);
	//printf("%d \n", buf);
	//return *line;
	
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
			/*for(i=0; i<sizeof(buffer); i+=1)
			{
				printf("%d\n", buffer[i]);
			}*/
			//printf("%d \n", buffer[pos]);
			//printf("%s\n", buffer);
			return *buffer; //"return buffer": returns integer from pointer without casting
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
	}
	//return line;
}
void main()
{
	read_line();
	//printf("%s\n", buffer);
}	
