#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
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

char *builtin[]={"cd", "help", "exit"}; //command names with their corresponding function mentioned in int (*builtin_func[])(char **)

int ccdd(char **args);
int help_me(char **args); //uses array of builtins and the array contains help_me(), so to break the chain
int exittt(char **args);


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
	printf("Format: Program_name Arguments (press EnTeR)");
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
