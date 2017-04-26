#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define BUFFER_SIZE 1024

char *line = "\ndkjfskdg\n";
char *buffer;
char *builtin[]={"cd", "help", "exit"}; //command names with their corresponding function mentioned in int (*builtin_func[])(char **)

int ccdd(char **args);
int help_me(char **args); //uses array of builtins and the array contains help_me(), so to break the chain
int exittt(char **args);

char *read_line() //readline() makes pointer from integer without cast
{
	int buf=BUFFER_SIZE;
	int pos=0;
	buffer=malloc(sizeof(char)*buf); //returns NULL if 0 size allocated
	int c, i;
	//char *line=NULL;
	//ssize_t buf=0;
	//getline(&line, &buf, stdin); //does entire line at a time
	//printf("%d \n", buf);
	//return *line;
	
	if(!buffer)
	{
		printf("M_sh:ALLOCATION ERROR \n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		c=getchar(); //character at a time
		if(c==-1 || c=='\n') //EOF=-1
		{
			buffer[pos]='\0';
			/*for(i=0; i<sizeof(buffer); i+=1)
			{
				printf("%d\n", buffer[i]);
			}*/
			//printf("%d \n", buffer[pos]);
			printf("%s\n", buffer);
			return buffer; //return buffer: returns integer from pointer without casting
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

#define DELIMITER "\t\n" 

char **tokenize(char *line) //tokenize(char *line) makes pointer from integer without casting
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

int start(char **args)
{
	pid_t pid, wpid;
	int stat;
	pid=fork();
	if(pid==0)
	{
		if (execvp(args[0], args) == -1) //if at all error occurs
		{
			perror("M_sh");
		}
		exit(EXIT_FAILURE);
	}
	else if(pid<0) //fork error
	{
		perror("M_sh");
	}
	else //means parent process will end up here and fork executed successfully
	{
		do
		{
			wpid=waitpid(pid, &stat, WUNTRACED); //return if child stopped working
		}while(!WIFEXITED(stat) && !WEXITSTATUS(stat));
			/*WIFEXITED(stat) returns TRUE if child terminated normally
					    WEXITSTATUS(stat) returns exit status of the CHILD*/
	}
	return -1;
}

int (*builtin_func[])(char **) = {&ccdd, &help_me, &exittt}; //easier when built-in commands are to be added.

int num_of_builtins()
{
	return sizeof(builtin)/sizeof(char *);
}

int ccdd(char **args)
{
	if(args[1] == NULL)
	{
		printf("M_sh: expected argument \"cd\"\n");
	}
	else
	{
		if(chdir(args[1]) != 0)
		{
			perror("M_sh");
		}
	}
	return 1;
}

int help_me(char **args)
{
	int i;
	printf("M_sh: Votrascii's Shell \n");
	printf("Format: Program_name Arguments (press EnTeR) \n");
	printf("Built-ins I've encorporated in are: \n");
	for(i = 0; i < num_of_builtins(); i += 1)
	{
		printf("%s\n", builtin[i]);
	}
	printf("'man' (command) and google are your best friends!! \n");
	return 1;
}

int exittt(char **args)
{
	return 0;
}

int execute(char **args) //mainly for putting together all the builtins
{
	int i;
	if(args[0] == NULL) //incase no commands are entered
	{
		return 1;
	}
	for(i=0; i < num_of_builtins(); i += 1)
	{
		if(strcmp(args[0], builtin[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}
	return start(args);
}
	
void M_sh()
{
	char *line;
	char **args;
	int stat;
	do
	{
		printf("M_sh: ");
		line=read_line();
		args=tokenize(line);
		stat=execute(args);
		free(line);
		free(args);
	}while(stat);
}

int main()
{
	M_sh();
	return EXIT_SUCCESS;
}
