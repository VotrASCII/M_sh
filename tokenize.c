#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE 1024
#define DELIMITER "\t\n"
char tokenize(char *line)
{
	int buf=BUFFER_SIZE, pos=0;
	char **tokens = malloc(buf*sizeof(char*)); //2D array dynamic allocation; array of pointers
	char *token;
	if(!tokens)
	{
		printf("M_sh:Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	token=strtok(line, DELIMITER); //returns pointer to the first token
	while(token!=NULL)
	{
		tokens[pos]=token; //storing character pointer in array of character pointers
		pos+=1;
		if(pos>=buf)
		{
			buf+=BUFFER_SIZE;
			tokens=realloc(tokens, buf*sizeof(char*)); //NULL terminated array of pointers to increase the array size
			if(!tokens)
			{
				printf("M_sh:Allocation Error\n");
				exit(EXIT_FAILURE);
			}
		}
		token=strtok(NULL, DELIMITER); //NULL terminating the list of token
	}
	tokens[pos]=NULL;
	return tokens;
}
	
